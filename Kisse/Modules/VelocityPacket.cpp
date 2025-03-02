#include "Modules.h"
#include "../../net/minecraft/network/play/server/S12PacketEntityVelocity/S12PacketEntityVelocity.h"


void Kisse::Modules::VelocityPacket::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
	ImGui::SliderFloat("motionX multiplier", &motionX_multiplier, -2.0f, 2.0f, "%.2f");
	ImGui::SliderFloat("motionY multiplier", &motionY_multiplier, -2.0f, 2.0f, "%.2f");
	ImGui::SliderFloat("motionZ multiplier", &motionZ_multiplier, -2.0f, 2.0f, "%.2f");
}

void Kisse::Modules::VelocityPacket::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
	if (!enabled) return;
	if (!packet.isValid()) return;
	if (!packet.instanceOf(Kisse::JavaClassV2("net/minecraft/network/play/server/S12PacketEntityVelocity").get_jclass(env))) return;

	S12PacketEntityVelocity velocityPacket(packet, env);
	if (velocityPacket.getEntityID() != Minecraft::getTheMinecraft(env).getThePlayer().getEntityId()) return;
	velocityPacket.setMotionX(int(velocityPacket.getMotionX() * motionX_multiplier));
	velocityPacket.setMotionY(int(velocityPacket.getMotionY() * motionY_multiplier));
	velocityPacket.setMotionZ(int(velocityPacket.getMotionZ() * motionZ_multiplier));
}