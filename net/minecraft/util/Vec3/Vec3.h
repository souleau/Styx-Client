#pragma once
#include "../../../../java/lang/Object/Object.h"
#include "../../../../Kisse/Maths/Maths.h"

class Vec3 : public Object {
public:
	using Object::Object;

	Kisse::Maths::Vector3d getVector() const;

	void setVector(const Kisse::Maths::Vector3d& vector);
protected:
	inline static Kisse::JavaClassV2 Vec3Class{ "net/minecraft/util/Vec3" };
};