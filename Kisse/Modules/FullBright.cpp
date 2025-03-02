#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>

void Kisse::Modules::FullBright::run()
{
	if (!enabled)
	{
		disable();
		return;
	}
	double gamma = Kisse::cache->gameSettings.getGammaSetting();
	if ( gamma != 50.0)
	{
		Kisse::cache->gameSettings.setGammaSetting(50.0);
		old_gamma = gamma;
	}
}

void Kisse::Modules::FullBright::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
}

void Kisse::Modules::FullBright::disable()
{
	if (!Kisse::p_env) return;
	if (old_gamma >= 0.0)
	{
		Kisse::cache->gameSettings.setGammaSetting(old_gamma);
		old_gamma = -1.0;
	}
}
