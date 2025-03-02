#pragma once
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include "../../java/util/Map/Map.h"
#include "../../net/minecraft/util/Timer/Timer.h"
#include "../../java/nio/FloatBuffer/FloatBuffer.h"
#include "../../java/nio/IntBuffer/IntBuffer.h"

namespace Kisse
{
	class Cache
	{
	public:
		Minecraft theMinecraft{Kisse::p_env, true};
		EntityPlayerSP thePlayer{ Kisse::p_env, true };
		PlayerControllerMP playerController{ Kisse::p_env, true };
		WorldClient theWorld{ Kisse::p_env, true };
		List playerEntities{ Kisse::p_env, true };
		GameSettings gameSettings{ Kisse::p_env, true };
		Timer timer{ Kisse::p_env, true };
		NetHandlerPlayClient sendQueue{ Kisse::p_env, true };

		bool fillCache();
		bool is_valid = false;
	private:
		EntityPlayerSP prev_thePlayer{ Kisse::p_env, true };
	};
	inline Cache* cache = new Cache();
}