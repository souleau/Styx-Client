#pragma once
#include "../../../world/World/World.h"

class WorldClient : public World {
public:
	using World::World;
	List getPlayerEntities() override;
protected:
	inline static Kisse::JavaClassV2 WorldClientClass{ "net/minecraft/client/multiplayer/WorldClient" };
};
