#include "EntityPlayerSP.h"

NetHandlerPlayClient EntityPlayerSP::getSendQueue()
{
	if (!instance)
		return NetHandlerPlayClient(nullptr, env);
	if (Kisse::version.type == Kisse::Version::MAJOR_1_7_10)
		return NetHandlerPlayClient(env->GetObjectField(instance, EntityPlayerMPClass.getFieldID("sendQueue")), env);
	return NetHandlerPlayClient(env->GetObjectField(instance, EntityPlayerSPClass.getFieldID("sendQueue")), env);
}
