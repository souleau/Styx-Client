#pragma once
#include "../../lang/Object/Object.h"
#include "../../../Kisse/Maths/Maths.h"

class FloatBuffer : public Object {
public:
	using Object::Object;
	float get(int index);
	Kisse::Maths::Matrix toMatrix(int lines, int columns);

protected:
	inline static Kisse::JavaClassV2 FloatBufferClass{ "java/nio/FloatBuffer" };
};
