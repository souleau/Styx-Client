#pragma once
#include "../Entity/Entity.h"

class EntityLivingBase : public Entity {
public:
	using Entity::Entity;
	void setPositionAndUpdate(const Kisse::Maths::Vector3d& position) override;
protected:
	inline static Kisse::JavaClassV2 EntityLivingBaseClass{ "net/minecraft/entity/EntityLivingBase" };
};