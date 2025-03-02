#include "Modules.h"
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include <imgui.h>
#include <chrono>
#include <thread>

class WTap {
public:
    WTap() : enabled(false), sprintDelay(0.0f) {}

    void onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel);
    void onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel);
    void renderGUI();

public:
    bool enabled;
    float sprintDelay; 
    int ticks = 0;
};


float sprintDelay;
void Kisse::Modules::WTap::onUpdateWalkingPlayer(JNIEnv* env, EntityPlayerSP& this_player, bool* cancel)
{
    if (!enabled) return;
    EntityPlayerSP thePlayer = Minecraft::getTheMinecraft(env).getThePlayer();
    if (thePlayer.isSprinting())
    {
        if (ticks >= sprintDelay * 20) {
            thePlayer.setSprinting(false);
            ticks = 0; 
        }
        else {
            ++ticks;
        }
    }
}

void Kisse::Modules::WTap::onAttackTargetEntityWithCurrentItem(JNIEnv* env, EntityPlayer& this_player, Entity& entity, bool* cancel)
{
    if (!enabled) return;
    ticks = 0;
}

void Kisse::Modules::WTap::renderGUI()
{
    ImGui::Checkbox("Enable", &enabled);
    ImGui::Text("Ticks: %d", static_cast<int>(sprintDelay * 20));
    ImGui::SliderFloat("Sprint Delay", &sprintDelay, 0.0f, 10.0f);
}
