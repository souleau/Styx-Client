#include "Modules.h"
#include <imgui.h>
#include "../Cache/Cache.h"

void Kisse::Modules::FastPlace::run()
{
	if (!enabled || !GetAsyncKeyState(VK_RBUTTON)) return;
	if (Kisse::cache->theMinecraft.getRightClickDelayTimer() == 4)
	{
		Kisse::cache->theMinecraft.setRightClickDelayTimer(tickDelay);
	}
}

void Kisse::Modules::FastPlace::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
	ImGui::SliderInt("Tick Delay", &tickDelay, 0, 3);
}