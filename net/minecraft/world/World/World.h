#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../java/util/List/List.h"
#include "../../block/state/IBlockState.h"
#include "../../util/BlockPos/BlockPos.h"
#include "../../../../Kisse/Maths/Maths.h"

class World : public Object
{
public:
	using Object::Object;
	IBlockState getBlockState(const BlockPos& blockPos);
	Block getBlock(const Kisse::Maths::Vector3d& position);
	virtual List getPlayerEntities();
protected:
	inline static Kisse::JavaClassV2 WorldClass{ "net/minecraft/world/World" };
	inline static Kisse::JavaClassV2 IBlockAccessClass{ "net/minecraft/world/IBlockAccess" };
};