#pragma once
#include "../../../java/lang/Object/Object.h"

class ChannelHandlerContext : public Object
{
public:
	using Object::Object;
protected:
	inline static Kisse::JavaClassV2 ChannelHandlerContextClass{ "io/netty/channel/ChannelHandlerContext" };
};