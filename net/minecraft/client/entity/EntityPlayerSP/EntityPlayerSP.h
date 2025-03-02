#pragma once
#include "../AbstractClientPlayer/AbstractClientPlayer.h"
#include "../../network/NetHandlerPlayClient/NetHandlerPlayClient.h"

class EntityPlayerSP : public AbstractClientPlayer {
public:
	using AbstractClientPlayer::AbstractClientPlayer;
	NetHandlerPlayClient getSendQueue();
protected:
	inline static Kisse::JavaClassV2 EntityPlayerSPClass{ "net/minecraft/client/entity/EntityPlayerSP" };
	inline static Kisse::JavaClassV2 EntityPlayerMPClass{ "net/minecraft/client/entity/EntityClientPlayerMP" };
};
