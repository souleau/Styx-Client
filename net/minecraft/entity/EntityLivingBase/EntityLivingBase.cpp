#include "EntityLivingBase.h"

void EntityLivingBase::setPositionAndUpdate(const Kisse::Maths::Vector3d& position)
{
	if (!instance)
		return;
	if (Kisse::version.type == Kisse::Version::MAJOR_1_7_10)
	{
		env->CallVoidMethod(
			instance,
			EntityLivingBaseClass.getMethodID("setPositionAndUpdate"),
			(jdouble)position.x,
			(jdouble)position.y,
			(jdouble)position.z);
		return;
	}
	Entity::setPositionAndUpdate(position);
	return;
}