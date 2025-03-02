#include "MovingObjectPosition.h"

MovingObjectType MovingObjectPosition::getType()
{
	if (!instance) return MovingObjectType(nullptr ,env);
	if (Kisse::version.type == Kisse::Version::MAJOR_1_16_5 || Kisse::version.type == Kisse::Version::MAJOR_1_19_4)
		return MovingObjectType(env->CallObjectMethod(instance, MovingObjectPositionClass.getMethodID("getType")), env);
	return MovingObjectType(env->GetObjectField(instance, MovingObjectPositionClass.getFieldID("typeOfHit")), env);
}
