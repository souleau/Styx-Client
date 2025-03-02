#pragma once
#include "../Collection/Collection.h"

class List : public Collection {
public:
	using Collection::Collection;
	static List newObject(JNIEnv* env = Kisse::p_env);
protected:
	inline static Kisse::JavaClassV2 ListClass{ "java/util/List" };
};