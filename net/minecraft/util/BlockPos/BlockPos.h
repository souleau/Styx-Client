#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../Kisse/Maths/Maths.h"

class BlockPos : public Object
{
public:
	using Object::Object;
	static BlockPos newObject(const Kisse::Maths::Vector3d& vector, JNIEnv* env = Kisse::p_env);
protected:
	inline static Kisse::JavaClassV2 BlockPosClass{ "net/minecraft/util/BlockPos" };
};