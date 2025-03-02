#include "Modules.h"

void Kisse::Modules::Speed::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
	ImGui::SliderFloat("Speed abpt", &speed, 0.01f, 2.0f, "%.2f");
}

void Kisse::Modules::Speed::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
	if (!enabled || !(GetKeyState(0x5A) & 0x8000) || !this_player.isOnGround()) return;
	Kisse::Maths::Vector3d motion = this_player.getMotion();
	Kisse::Maths::Vector3d additional = Kisse::Maths::getCameraVector(this_player.getRotation(), speed);
	motion.x += additional.x;
	motion.z += additional.z;
	this_player.setMotion(motion);
}