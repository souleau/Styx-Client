#pragma once
#include "../Object/Object.h"

class String : public Object {
public:
	using Object::Object;
	String(const std::string& str, JNIEnv* env = Kisse::p_env);
	String(const char* str, JNIEnv* env = Kisse::p_env);
	int size() const;
	int modifiedUTF8size() const;
	std::string toStdString() const;
protected:
	inline static Kisse::JavaClassV2 StringClass{ "java/lang/String" };
};
