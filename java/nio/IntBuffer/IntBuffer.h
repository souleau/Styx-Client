#pragma once
#include "../../lang/Object/Object.h"
#include "../../../Kisse/Maths/Maths.h"

class IntBuffer : public Object {
public:
	using Object::Object;
	int get(int index);
	Kisse::Maths::Matrix toMatrix(int lines, int columns);

protected:
	inline static Kisse::JavaClassV2 IntBufferClass{ "java/nio/IntBuffer" };
};