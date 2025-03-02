#include "Modules.h"

void Kisse::Modules::VelocityFly::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
	ImGui::SliderFloat("Speed", &speed, 0.01f, 2.0f, "%.2f");
}

void Kisse::Modules::VelocityFly::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
	if (!enabled) return;
	Kisse::Maths::Vector3d motion = this_player.getMotion();

	if (GetKeyState(0x5A) & 0x8000)
	{
		Kisse::Maths::Vector3d additional = Kisse::Maths::getCameraVector(this_player.getRotation(), speed);
		motion.x += additional.x;
		motion.z += additional.z;
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
		motion.y = speed;
	else if (GetKeyState(VK_LSHIFT) & 0x8000)
		motion.y = -speed;
	else motion.y = 0.0;

	if (!this_player.isOnGround())
		this_player.setMotion(motion);
}