#include "Modules.h"
#include <imgui.h>
#include "../Hook/JavaHook.h"
#include "../Cache/Cache.h"
#include "../../net/minecraft/client/renderer/ActiveRenderInfo/ActiveRenderInfo.h"
#include "../GUI/GUI.h"


void Kisse::Modules::Xray::renderGUI()
{

	ImGui::Checkbox("Enable", &enabled);
	ImGui::SliderInt("Radius", &RADIUS, 5, 50);
	ImGui::Checkbox("Coal", &coal);
	ImGui::Checkbox("Redstone", &redstone);
	ImGui::Checkbox("Diamond", &diamond);
	ImGui::Checkbox("Gold", &gold);
	ImGui::Checkbox("Iron", &iron);
	ImGui::Checkbox("Emerald", &emerald);
	ImGui::Checkbox("Lapis", &lapis);
	ImGui::Checkbox("Other", &other);
}

void Kisse::Modules::Xray::render()
{
	if (!enabled || !Kisse::cache->is_valid)
	{
		update_blocks = false;
		return;
	}
	update_blocks = true;

	ImVec2 screenSize = ImGui::GetWindowSize();

	Kisse::Maths::Matrix modelView = ActiveRenderInfo::get_cached_MODELVIEW();
	Kisse::Maths::Matrix projection = ActiveRenderInfo::get_cached_PROJECTION();
	Kisse::Maths::Vector3d cameraPos = ActiveRenderInfo::get_cached_cameraPos();

	std::lock_guard lock{ renderData_mutex };
	for (RenderData& renderData : renderDatas)
	{
		if (!renderData.render) continue;
		for (RenderData::Quad& quad : renderData.quads)
		{
			Kisse::Maths::Vector2d p1{}, p2{}, p3{}, p4{};
			if
			(
				!Kisse::Maths::worldToScreen(quad.p1 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p1)
				|| !Kisse::Maths::worldToScreen(quad.p2 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p2)
				|| !Kisse::Maths::worldToScreen(quad.p3 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p3)
				|| !Kisse::Maths::worldToScreen(quad.p4 - cameraPos, modelView, projection, (int)screenSize.x, (int)screenSize.y, p4)
			)
				continue;
			ImGui::GetWindowDrawList()->AddQuad(ImVec2((float)p1.x, (float)p1.y), ImVec2((float)p2.x, (float)p2.y), ImVec2((float)p3.x, (float)p3.y), ImVec2((float)p4.x, (float)p4.y), renderData.color, 2.0f);
		}
	}
}

void Kisse::Modules::Xray::disable()
{
	thread_running = false;
	blockFinderThread.join();
}

void Kisse::Modules::Xray::updateRenderData(Xray* xray)
{
	JavaVM* jvm = nullptr;
	JNI_GetCreatedJavaVMs(&jvm, 1, nullptr);
	if (!jvm) return;
	JNIEnv* env = nullptr;
	jvm->AttachCurrentThreadAsDaemon((void**)&env, nullptr);
	if (!env) return;

	while (xray->thread_running && (!xray->update_blocks || !Kisse::cache->is_valid));

	{
		Kisse::JNIFrame frame(env, 10);
		Minecraft theMinecraft = Minecraft::getTheMinecraft(env);

		while (xray->thread_running)
		{
			static Kisse::CTimer timer(std::chrono::milliseconds(1000));
			if (!xray->update_blocks || !Kisse::cache->is_valid || !timer.isElapsed()) continue;

			Kisse::JNIFrame frame(env, 10);
			World theWorld = theMinecraft.getTheWorld();

			Kisse::Maths::Vector3d thePlayerPos = theMinecraft.getThePlayer().getPosition();
			thePlayerPos.x = std::floor(thePlayerPos.x);
			thePlayerPos.y = std::floor(thePlayerPos.y);
			thePlayerPos.z = std::floor(thePlayerPos.z);
			int base_x = (int)thePlayerPos.x - xray->RADIUS, base_y = (int)thePlayerPos.y - xray->RADIUS, base_z = (int)thePlayerPos.z - xray->RADIUS;

			std::vector<RenderData> data_cache{};

			for (int x = 0; x < 2 * xray->RADIUS; ++x)
			{
				Kisse::JNIFrame frame(env, 4 * xray->RADIUS * xray->RADIUS);
				for (int y = 0; y < 2 * xray->RADIUS; ++y)
				{
					for (int z = 0; z < 2 * xray->RADIUS; ++z)
					{
						Kisse::Maths::Vector3d pos1(base_x + x, base_y + y, base_z + z);
						Block block = theWorld.getBlock(pos1);
						std::string name = block.getName();
						if(name.find("ore") != std::string::npos)
							data_cache.push_back(RenderData(pos1, name, xray));
					}
				}
			}

			std::lock_guard lock{ xray->renderData_mutex };
			xray->renderDatas.clear();
			for (RenderData& data : data_cache)
				xray->renderDatas.push_back(data);
		}

	}
	jvm->DetachCurrentThread();
}

Kisse::Modules::Xray::RenderData::RenderData(const Kisse::Maths::Vector3d& blockPos, const std::string& blockName, Xray* xray) :
	quads
	{ 
		RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x, blockPos.y, blockPos.z + 1}},
		RenderData::Quad{{blockPos.x, blockPos.y + 1, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}},
		RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}, {blockPos.x, blockPos.y + 1, blockPos.z}},
		RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}},
		RenderData::Quad{{blockPos.x, blockPos.y, blockPos.z}, {blockPos.x, blockPos.y, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z + 1}, {blockPos.x, blockPos.y + 1, blockPos.z}},
		RenderData::Quad{{blockPos.x + 1, blockPos.y, blockPos.z}, {blockPos.x + 1, blockPos.y, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z + 1}, {blockPos.x + 1, blockPos.y + 1, blockPos.z}}
	}
{
	bool diamond = blockName.find("diamond") != std::string::npos;
	bool gold = blockName.find("gold") != std::string::npos;
	bool iron = blockName.find("iron") != std::string::npos;
	bool lapis = blockName.find("lapis") != std::string::npos;
	bool emerald = blockName.find("emerald") != std::string::npos;
	bool redstone = blockName.find("redstone") != std::string::npos;
	bool coal = blockName.find("coal") != std::string::npos;

	if (xray->diamond && diamond)
		color = { 76, 229, 237, 40 };
	else if (xray->gold && gold)
		color = { 252, 252, 68, 40 };
	else if (xray->iron && iron)
		color = { 186, 112, 34, 40 };
	else if (xray->lapis && lapis)
		color = { 42, 67, 250, 40 };
	else if (xray->emerald && emerald)
		color = { 20, 184, 20, 40 };
	else if (xray->redstone && redstone)
		color = { 255, 41, 41, 40 };
	else if (xray->coal && coal)
		color = { 23, 21, 21, 40 };
	else if (xray->other && !diamond && !gold && !iron && !lapis && !emerald && !redstone && !coal)
		color = { 209, 100, 245, 40 };
	else
		render = false;
}
