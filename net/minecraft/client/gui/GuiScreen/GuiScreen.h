#pragma once
#include "../../../../../java/lang/Object/Object.h"

class GuiScreen : public Object
{
public:
	using Object::Object;
protected:
	inline static Kisse::JavaClassV2 GuiScreenClass{ "net/minecraft/client/gui/GuiScreen" };
};