#include "Modules.h"
#include "../Hook/JavaHook.h"

void Kisse::Modules::NoMiss::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
}

void Kisse::Modules::NoMiss::onClickMouse(JNIEnv* env, Minecraft& theMinecraft, bool* cancel)
{
	if (!enabled) return;
	if (theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("MISS", env)))
	{
		Kisse::JavaHook::set_return_value<uint64_t>(cancel, 0);
		*cancel = true;
	}
}