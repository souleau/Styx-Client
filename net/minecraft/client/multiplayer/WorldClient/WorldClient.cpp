#include "WorldClient.h"
#include "../../../../java/util/List/List.h"

List WorldClient::getPlayerEntities()
{
	if (!instance) return List(nullptr, env);
	if (Kisse::version.type == Kisse::Version::MAJOR_1_16_5 || Kisse::version.type == Kisse::Version::MAJOR_1_19_4)
		return List(env->GetObjectField(instance, WorldClientClass.getFieldID("players")), env);
	return World::getPlayerEntities();
}
