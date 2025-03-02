#include "Modules.h"
#include "../GUI/GUI.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../Kisse/Modules/LeftClicker.h"
#include <random>
#include <Windows.h>

//bool exhaustModeActive = false;

namespace clicker {
    enum ClickerMode {
        BUTTER,
        JITTER,
        BLATANT,
        CUSTOM,
        CUSTOM2,
        EXHAUST

    };

    inline ClickerMode currentMode;
}
bool isInMenuEnabled = false;

bool breakactive = false;
float Randomization() {
    switch (clicker::currentMode) {
    case clicker::BUTTER:
        return static_cast<float>(Random::GenerateNum(775, 1650) / clicker::CPS);
    case clicker::JITTER:
        return static_cast<float>(Random::GenerateNum(850, 1450) / clicker::CPS);
        /*
    case clicker::BLATANT:
        return static_cast<float>(Random::GenerateNum(975, 1050) / clicker::CPS);
    case clicker::CUSTOM:
        return static_cast<float>(Random::GenerateNum(267, 1730) / clicker::CPS);
        /*
    case clicker::CUSTOM2:
        return static_cast<float>(Random::GenerateNum(267, 1730 || 467 || 754) / clicker::CPS);
        */
    default:
        return 0.0f;
    }
}

bool IsInMenu() {
    if (!isInMenuEnabled)
        return false;

    CURSORINFO pci;
    pci.cbSize = sizeof(CURSORINFO);

    GetCursorInfo(&pci);
    if (reinterpret_cast<int>(pci.hCursor) > 100000)
        return false;

    return true;
}


bool inventoryClickEnabled = false;



void Kisse::Modules::Autoclicker::run() {
    static CTimer timer(std::chrono::milliseconds(1000 / clicker::CPS));
    if (!enabled || Kisse::GUI::draw || !(GetKeyState(VK_LBUTTON) & 0x8000) || cache->theMinecraft.getCurrentScreen().isValid())
        return;
    if (!timer.isElapsed())
        return;
    if (breakactive && Kisse::cache->theMinecraft.getObjectMouseOver().getType().isEqualTo(MovingObjectType::getType("BLOCK")))
        return;

    POINT cursorPos{};
    GetCursorPos(&cursorPos);
    PostMessageA(Kisse::window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));
    PostMessageA(Kisse::window, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(cursorPos.x, cursorPos.y));

    timer.setEvery(std::chrono::milliseconds(static_cast<int>(Randomization())));
}







void Kisse::Modules::Autoclicker::renderGUI() {


    ImGui::Checkbox("Enable", &enabled);
    static bool unlocker = false;
   // ImGui::Checkbox("Exhaust", &exhaustModeActive);
    ImGui::Checkbox("cps unlocker", &unlocker);
  //  ImGui::Checkbox("Inventory Click", &inventoryClickEnabled);

    float cpsMin = 5.0f;
    float cpsMax = unlocker ? 50.0f : 25.0f;
    float cps = clicker::CPS; 
    ImGui::SliderFloat("CPS", &cps, cpsMin, cpsMax, "%.1f");

    clicker::CPS = cps;

    ImGui::Checkbox("IsInMenu", &isInMenuEnabled);
    ImGui::SameLine();
    ImGui::Checkbox("Break Block", &breakactive);
    ImGui::NewLine();
    const char* items[] = { "Butter", "Jitter" };
    static int item_current = 0;
    ImGui::Combo("Click Method", &item_current, items, IM_ARRAYSIZE(items));


    switch (item_current) {
    case 0: // Butter
        clicker::currentMode = clicker::BUTTER;
        cps = 22.0f;
        break;
    case 1: // Jitter
        clicker::currentMode = clicker::JITTER;
        break;
        /*
    case 2: // Blatant
        clicker::currentMode = clicker::BLATANT;
        break;
    case 3: // Custom
        clicker::currentMode = clicker::CUSTOM;
        break;
        /*
    case 4: // Custom
        clicker::currentMode = clicker::CUSTOM2;
        break;
        */
    default:
        break;
    }

    

}