#include "Modules.h"
#include "../Cache/Cache.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C06PacketPlayerPosLook/C06PacketPlayerPosLook.h"

void Kisse::Modules::NoFall::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
}

void Kisse::Modules::NoFall::onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel)
{
	if (!enabled) return;
	if (!packet.instanceOf(Kisse::JavaClassV2("net/minecraft/network/play/client/C03PacketPlayer").get_jclass(env))) return;
	C03PacketPlayer packetPlayer(packet);
	packetPlayer.setOnGround(true);
}
