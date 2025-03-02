#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../Hook/JavaHook.h"

void Kisse::Modules::Blink::run()
{
}

void Kisse::Modules::Blink::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
	ImGui::Checkbox("delay sent", &delay_sent_packets);
	ImGui::Checkbox("delay received", &delay_received_packets);
}

void Kisse::Modules::Blink::disable()
{
	if (!Kisse::p_env || !Kisse::cache || !Kisse::cache->is_valid) return;
	sendPackets(Kisse::cache->sendQueue);
	sendrPackets(Kisse::p_env);
}

void Kisse::Modules::Blink::onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel)
{
	if (!enabled || !delay_sent_packets)
	{
		if (!packets.empty())
			sendPackets(sendQueue);
		return;
	}
	if (!packet.isValid()) return;
	*cancel = true;
	packets.push_back(packet);
}

void Kisse::Modules::Blink::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
	if (!enabled || !delay_received_packets)
	{
		if (!rpackets.empty()) sendrPackets(env);
		return;
	}
	if (!packet.isValid()) return;
	*cancel = true;
	addrPacket({ this_networkManager , context,  packet });
}

void Kisse::Modules::Blink::sendPackets(NetHandlerPlayClient& sendQueue)
{
	onAddToSendQueueNoEvent = true;
	for (Packet& packet : packets)
		sendQueue.addToSendQueue(packet);
	packets.clear();
	onAddToSendQueueNoEvent = false;
}

void Kisse::Modules::Blink::sendrPackets(JNIEnv* env)
{
	onChannelRead0NoEvent = true;
	std::lock_guard lock{ rpackets_mutex };
	for (PacketData& data : rpackets)
	{ 
		data.this_networkManager.set_env(env);
		data.this_networkManager.channelRead0(data.context, data.packet);
	}
	rpackets.clear();
	onChannelRead0NoEvent = false;
}

void Kisse::Modules::Blink::addrPacket(const PacketData& data)
{
	std::lock_guard lock{ rpackets_mutex };
	rpackets.push_back(data);
}
