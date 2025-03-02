#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>


void Kisse::Modules::Velocity::run()
{
	if (!enabled) return;
	if (Kisse::cache->thePlayer.getHurtResistantTime() != 20 - tickDelay) return;

	Kisse::Maths::Vector3d motion = Kisse::cache->thePlayer.getMotion();
	motion.x *= motionX;
	motion.y *= motionY;
	motion.z *= motionZ;
	Kisse::cache->thePlayer.setMotion(motion);
}

void Kisse::Modules::Velocity::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
	ImGui::SliderFloat("Motion X", &motionX, -2.0f, 2.0f, "%.1f");
	ImGui::SliderFloat("Motion Y", &motionY, -2.0f, 2.0f, "%.1f");
	ImGui::SliderFloat("Motion Z", &motionZ, -2.0f, 2.0f, "%.1f");
	ImGui::SliderInt("Tick Delay", &tickDelay, 0, 20);
}
