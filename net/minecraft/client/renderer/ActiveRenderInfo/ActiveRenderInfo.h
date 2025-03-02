#pragma once
#include "../../../../../java/lang/Object/Object.h"
#include "../../../../../java/nio/FloatBuffer/FloatBuffer.h"

class ActiveRenderInfo : public Object
{
public:
	using Object::Object;
	static FloatBuffer getMODELVIEW(JNIEnv* env = Kisse::p_env);
	static FloatBuffer getPROJECTION(JNIEnv* env = Kisse::p_env);
	static void update_cache(JNIEnv* env = Kisse::p_env);
	static Kisse::Maths::Matrix get_cached_MODELVIEW();
	static Kisse::Maths::Matrix get_cached_PROJECTION();
	static Kisse::Maths::Vector3d get_cached_cameraPos();
	static void set_MODELVIEW(Kisse::Maths::Matrix& modelview)
	{
		MODELVIEW = modelview;
	}
	static void set_PROJECTION(Kisse::Maths::Matrix& projection)
	{
		PROJECTION = projection;
	}
protected:
	inline static Kisse::JavaClassV2 ActiveRenderInfoClass{ "net/minecraft/client/renderer/ActiveRenderInfo" };
private:
	inline static Kisse::Maths::Matrix MODELVIEW = { {0} };
	inline static Kisse::Maths::Matrix PROJECTION = { {0} };
	inline static Kisse::Maths::Vector3d cameraPos = { 0.0, 0.0, 0.0 };
};