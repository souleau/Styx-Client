#include "Modules.h"
#include <ImGui/imgui.h>
#include "../Cache/Cache.h"

void Kisse::Modules::Sprint::run()
{
	if (!enabled)
		return;
	cache->gameSettings.getKeyBindSprint().setPressed(true);
}

void Kisse::Modules::Sprint::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
}