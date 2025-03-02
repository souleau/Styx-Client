#pragma once
#include "../Object/Object.h"

class System : public Object {
public:
	using Object::Object;
	static void gc(JNIEnv* env = Kisse::p_env);
protected:
	inline static Kisse::JavaClassV2 SystemClass{ "java/lang/System" };
};
