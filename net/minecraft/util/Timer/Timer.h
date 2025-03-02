#pragma once
#include "../../../../java/lang/Object/Object.h"

class Timer : public Object {
public:
	using Object::Object;
	float getRenderPartialTicks();
protected:
	inline static Kisse::JavaClassV2 TimerClass{ "net/minecraft/util/Timer" };
};