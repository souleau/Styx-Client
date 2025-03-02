#pragma once
#include "../../EntityLivingBase/EntityLivingBase.h"

class EntityPlayer : public EntityLivingBase {
public:
	using EntityLivingBase::EntityLivingBase;
protected:
	inline static Kisse::JavaClassV2 EntityPlayerClass{ "net/minecraft/entity/player/EntityPlayer" };
};