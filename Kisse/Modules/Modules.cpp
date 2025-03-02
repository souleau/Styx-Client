#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../Hook/JavaHook.h"

Kisse::Modules::IModule::IModule(const char* name) : name(name)
{
}

const char* Kisse::Modules::IModule::get_name()
{
	return name;
}

void Kisse::Modules::IModule::run()
{
}

void Kisse::Modules::IModule::renderGUI()
{
}

void Kisse::Modules::IModule::render()
{
}

void Kisse::Modules::IModule::disable()
{
	//enabled = false;
}

void Kisse::Modules::IModule::onAddToSendQueue(JNIEnv* env, NetHandlerPlayClient& sendQueue, Packet& packet, bool* cancel)
{
}

void Kisse::Modules::IModule::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
}

void Kisse::Modules::IModule::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
}

void Kisse::Modules::IModule::onGetMouseOver(JNIEnv* env, float partialTicks, bool* cancel)
{
}

void Kisse::Modules::IModule::onGetClientModName(JNIEnv* env, bool* cancel)
{
}

void Kisse::Modules::IModule::onChannelRead0(JNIEnv* env, NetworkManager& this_networkManager, ChannelHandlerContext& context, Packet& packet, bool* cancel)
{
}

void Kisse::Modules::IModule::onClickMouse(JNIEnv* env, Minecraft& theMinecraft, bool* cancel)
{
}

void Kisse::Modules::IModule::onKeyBind(int keyBind)
{
	if (!keyBind || keyBind != this->keyBind) return;
	enabled = !enabled;
}

static void addToSendQueue_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Kisse::p_env) return;
	if (Kisse::Modules::IModule::onAddToSendQueueNoEvent) return;
	JNIEnv* env = thread->get_env();

	NetHandlerPlayClient sendQueue(Kisse::JavaHook::get_jobject_param_at(frame, 0), env, true);
	Packet packet(Kisse::JavaHook::get_jobject_param_at(frame, 1), env, true);

	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (Kisse::Modules::IModule* module : category.modules)
		{
			Kisse::JNIFrame frame(env);
			module->onAddToSendQueue(env, sendQueue, packet, cancel);
		}
	}

	return;
}

static void getMouseOver_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Kisse::p_env) return;
	JNIEnv* env = thread->get_env();

	float f = Kisse::JavaHook::get_primitive_param_at<float>(frame, 1);
	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (Kisse::Modules::IModule* module : category.modules)
		{
			module->onGetMouseOver(env, f, cancel);
		}
	}
	return;
}

static void attackTargetEntityWithCurrentItem_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Kisse::p_env) return;
	JNIEnv* env = thread->get_env();

	EntityPlayer this_player(Kisse::JavaHook::get_jobject_param_at(frame, 0), env, true);
	Entity entity(Kisse::JavaHook::get_jobject_param_at(frame, 1), env, true);

	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (Kisse::Modules::IModule* module : category.modules)
		{
			Kisse::JNIFrame frame(env);
			module->onAttackTargetEntityWithCurrentItem(env, this_player, entity, cancel);
		}
	}

	return;
}

static void onUpdateWalkingPlayer_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Kisse::p_env) return;
	JNIEnv* env = thread->get_env();

	EntityPlayerSP this_player(Kisse::JavaHook::get_jobject_param_at(frame, 0), env, true);

	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (Kisse::Modules::IModule* module : category.modules)
		{
			Kisse::JNIFrame frame(env);
			module->onUpdateWalkingPlayer(env, this_player, cancel);
		}
	}

	return;
}

static void getClientModName_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Kisse::p_env) return;
	JNIEnv* env = thread->get_env();

	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (Kisse::Modules::IModule* module : category.modules)
		{
			Kisse::JNIFrame frame(env);
			module->onGetClientModName(env, cancel);
		}
	}
	return;
}

static void channelRead0_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Kisse::p_env || Kisse::Modules::IModule::onChannelRead0NoEvent) return;
	JNIEnv* env = thread->get_env();

	NetworkManager this_networkManager(Kisse::JavaHook::get_jobject_param_at(frame, 0), env, true);
	ChannelHandlerContext context(Kisse::JavaHook::get_jobject_param_at(frame, 1), env, true);
	Packet packet(Kisse::JavaHook::get_jobject_param_at(frame, 2), env, true);

	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (Kisse::Modules::IModule* module : category.modules)
		{
			Kisse::JNIFrame frame(env);
			module->onChannelRead0(env, this_networkManager, context, packet, cancel);
		}
	}
	return;
}

static void clickMouse_callback(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
	if (!Kisse::p_env) return;
	JNIEnv* env = thread->get_env();

	Minecraft theMinecraft(Kisse::JavaHook::get_jobject_param_at(frame, 0), env, true);

	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (Kisse::Modules::IModule* module : category.modules)
		{
			Kisse::JNIFrame frame(env);
			module->onClickMouse(env, theMinecraft, cancel);
		}
	}
	return;
}

void Kisse::Modules::setupEventHooks()
{
	Kisse::JavaClassV2 NetHandlerPlayClient("net/minecraft/client/network/NetHandlerPlayClient");
	jmethodID addToSendQueue = NetHandlerPlayClient.getMethodID("addToSendQueue");
	Kisse::JavaHook::hook(addToSendQueue, addToSendQueue_callback);

	Kisse::JavaClassV2 EntityRenderer("net/minecraft/client/renderer/EntityRenderer");
	jmethodID getMouseOver = EntityRenderer.getMethodID("getMouseOver");
	Kisse::JavaHook::hook(getMouseOver, getMouseOver_callback);

	Kisse::JavaClassV2 EntityPlayer("net/minecraft/entity/player/EntityPlayer");
	jmethodID attackTargetEntityWithCurrentItem = EntityPlayer.getMethodID("attackTargetEntityWithCurrentItem");
	Kisse::JavaHook::hook(attackTargetEntityWithCurrentItem, attackTargetEntityWithCurrentItem_callback);

	Kisse::JavaClassV2 EntityPlayerSP
	(
		(Kisse::version.type == Kisse::Version::MAJOR_1_7_10 ? "net/minecraft/client/entity/EntityClientPlayerMP" 
			: "net/minecraft/client/entity/EntityPlayerSP")
	);
	jmethodID onUpdateWalkingPlayer = EntityPlayerSP.getMethodID("onUpdateWalkingPlayer");
	Kisse::JavaHook::hook(onUpdateWalkingPlayer, onUpdateWalkingPlayer_callback);

	Kisse::JavaClassV2 ClientBrandRetriever("net/minecraft/client/ClientBrandRetriever");
	jmethodID getClientModName = ClientBrandRetriever.getMethodID("getClientModName");
	Kisse::JavaHook::hook(getClientModName, getClientModName_callback);

	Kisse::JavaClassV2 NetworkManager("net/minecraft/network/NetworkManager");
	jmethodID channelRead0 = NetworkManager.getMethodID("channelRead0");
	Kisse::JavaHook::hook(channelRead0, channelRead0_callback);

	Kisse::JavaClassV2 Minecraft("net/minecraft/client/Minecraft");
	jmethodID clickMouse = Minecraft.getMethodID("clickMouse");
	Kisse::JavaHook::hook(clickMouse, clickMouse_callback);
}

void Kisse::Modules::runAll()
{
	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (IModule* m : category.modules)
		{
			m->run();
		}
	}
}

void Kisse::Modules::cleanAll()
{
	for (Kisse::Modules::Category& category : Kisse::Modules::categories)
	{
		for (IModule* m : category.modules)
		{
			m->disable();
		}
	}
}


void Kisse::Modules::ESP::render()
{
}
float holdDuration = 1.0f;
void Kisse::Modules::BlockOnAttack::renderGUI()
{
	ImGui::Checkbox("Enable", &enabled);
	ImGui::SliderFloat("Tick", &holdDuration, 0.1f, 10.0f);
}

auto startTime = std::chrono::high_resolution_clock::now();
//bool enabled = false;
void Kisse::Modules::BlockOnAttack::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
	if (!enabled) return;

	POINT cursorPos{};
	GetCursorPos(&cursorPos);

	float holdDurationInSeconds = holdDuration;

	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsedTime = currentTime - startTime;

	if (elapsedTime.count() >= holdDurationInSeconds)
	{
		PostMessageA(Kisse::window, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
		startTime = std::chrono::high_resolution_clock::now();

	}

}