#include "ActiveRenderInfo.h"
#include "../../../util/Vec3/Vec3.h"
#include "../../../../../Kisse/Cache/Cache.h"

FloatBuffer ActiveRenderInfo::getMODELVIEW(JNIEnv* env)
{
	return FloatBuffer
	(
		env->GetStaticObjectField(ActiveRenderInfoClass.get_jclass(env), ActiveRenderInfoClass.getFieldID("MODELVIEW")),
		env
	);
}

FloatBuffer ActiveRenderInfo::getPROJECTION(JNIEnv* env)
{
	return FloatBuffer
	(
		env->GetStaticObjectField(ActiveRenderInfoClass.get_jclass(env), ActiveRenderInfoClass.getFieldID("PROJECTION")),
		env
	);
}

void ActiveRenderInfo::update_cache(JNIEnv* env)
{
	MODELVIEW = ActiveRenderInfo::getMODELVIEW(env).toMatrix(4, 4);
	PROJECTION = ActiveRenderInfo::getPROJECTION(env).toMatrix(4, 4);
	cameraPos = Kisse::cache->theMinecraft.getRenderViewEntity().getRenderPos(Kisse::cache->timer.getRenderPartialTicks());
}

Kisse::Maths::Matrix ActiveRenderInfo::get_cached_MODELVIEW()
{
	return MODELVIEW;
}

Kisse::Maths::Matrix ActiveRenderInfo::get_cached_PROJECTION()
{
	return PROJECTION;
}

Kisse::Maths::Vector3d ActiveRenderInfo::get_cached_cameraPos()
{
	return cameraPos;
}
