#include "Modules.h"
#include "../Cache/Cache.h"
#include "../../java/lang/String/String.h"
#include <ImGui/imgui.h>

float y_expand = false;

void Kisse::Modules::Reach::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
	ImGui::SliderFloat("Reach", &reach_distance, 3.0f, 6.0f, "%.2f");

	static bool showYExpandSlider = false;
	if (ImGui::Checkbox("Same Y", &showYExpandSlider))
	{

		//showYExpandSlider = !showYExpandSlider;
	}

	if (showYExpandSlider)
	{
		ImGui::SliderFloat("Y Expand ", &y_expand, 0.01f, 2.0f, "%.2f");
	};
}

void Kisse::Modules::Reach::disable()
{
	if (!cp_reach_addr) return;
	if (Kisse::p_env)
	{ 
		*cp_reach_addr = ((Kisse::version.type == Kisse::Version::MAJOR_1_16_5 || Kisse::version.type == Kisse::Version::MAJOR_1_19_4) ? 9.0 : 3.0);
		_constMethod->set_constants(original_constant_pool);
	}
	VirtualFree(new_constant_pool, 0, MEM_RELEASE);
}

void Kisse::Modules::Reach::onGetMouseOver(JNIEnv* env, float partialTicks, bool* cancel)
{
	static float prev_reach_distance = -1.0f;
	static bool runonce = true;
	if (!enabled)
	{
		if (!cp_reach_addr) return;
		if (prev_reach_distance != -1.0f)
		{
			*cp_reach_addr = ((Kisse::version.type == Kisse::Version::MAJOR_1_16_5 || Kisse::version.type == Kisse::Version::MAJOR_1_19_4) ? 9.0 : 3.0);
			prev_reach_distance = -1.0f;
		}
		return;
	}

	if (runonce)
	{
		Kisse::JavaClassV2 EntityRenderer("net/minecraft/client/renderer/EntityRenderer");
		jmethodID mid = EntityRenderer.getMethodID("getMouseOver");
		HotSpot::Method* method = *((HotSpot::Method**)mid);
		_constMethod = method->get_constMethod();
		original_constant_pool = _constMethod->get_constants();

		int cp_length = original_constant_pool->get_length();
		int cp_size = cp_length * 8 + HotSpot::ConstantPool::get_size();

		new_constant_pool = (HotSpot::ConstantPool*)Kisse::Module::allocate_nearby_memory((uint8_t*)original_constant_pool, cp_size, PAGE_READWRITE);
		memcpy(new_constant_pool, original_constant_pool, cp_size);
		_constMethod->set_constants(new_constant_pool);

		double* constant_pool_base = (double*)new_constant_pool->get_base();
		for (int i = 0; i < cp_length; ++i)
		{
			double* d = constant_pool_base + i;
			if (*d == ((Kisse::version.type == Kisse::Version::MAJOR_1_16_5 || Kisse::version.type == Kisse::Version::MAJOR_1_19_4) ? 9.0 : 3.0))
			{
				cp_reach_addr = d;
				break;
			}
		}
		runonce = false;
	}

	if (!cp_reach_addr) return;
	float d = ((Kisse::version.type == Kisse::Version::MAJOR_1_16_5 || Kisse::version.type == Kisse::Version::MAJOR_1_19_4) ? reach_distance * reach_distance : reach_distance);
	if (prev_reach_distance == d) return;
	*cp_reach_addr = (double)d;
	prev_reach_distance = d;
}


