#include "Modules.h"
#include <ImGui/imgui.h>
#include "../Cache/Cache.h"
#include <thread> 
#include <chrono>

int lagSwitch_val = 80;
bool enabled = false;
// lagSwitch = false;
bool prev_lagswitch = false;
std::string lag_rule_name = "";

void Kisse::Modules::Criticals::renderGUI()
{
    ImGui::Checkbox("Enable", &enabled);
  //  ImGui::SliderInt("LagSwitch Value", &lagSwitch_val, 0, 1000);

    std::vector<std::string> comboOptions = { "Normal", "HitSelect" };


    static int selectedOption = 0; 


    if (ImGui::BeginCombo("Mode", comboOptions[selectedOption].c_str()))
    {
        for (int i = 0; i < comboOptions.size(); i++)
        {
            bool isSelected = (selectedOption == i);
            if (ImGui::Selectable(comboOptions[i].c_str(), isSelected))
            {
                selectedOption = i;

              
                if (comboOptions[i] == "HitSelect")
                {
                    lagSwitch_val = 80;
                }
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

}

std::string RandomString(int length) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, chars.size() - 1);
    std::string random_string;
    for (int i = 0; i < length; ++i) {
        random_string += chars[distribution(rng)];
    }
    return random_string;
}


std::string lagcmd;
int prev_lagSwitch_val = -1;
bool reset_lagswitch = false;
bool reset_lagswitch_pt1 = false;

void Kisse::Modules::Criticals::run()
{
    while (true) {
        if (!enabled && (lagSwitch_val != prev_lagSwitch_val)) {
            prev_lagSwitch_val = lagSwitch_val;
            reset_lagswitch = true;
        }

        if ((enabled && !prev_lagswitch) || reset_lagswitch_pt1) {
            prev_lagswitch = true;
            // activer le lagswitch
            lag_rule_name = RandomString(8);
            lagcmd = "powershell \"New-NetQosPolicy -Name " + lag_rule_name + " -AppPathNameMatchCondition javaw.exe -ThrottleRateActionBitsPerSecond " + std::to_string(lagSwitch_val) + "kb -PolicyStore ActiveStore\"";
            system(lagcmd.c_str());

            if (reset_lagswitch) {
                reset_lagswitch = false;
                reset_lagswitch_pt1 = false;
            }
        }
        else if ((!enabled && prev_lagswitch) || reset_lagswitch) {
            if (!reset_lagswitch)
                prev_lagswitch = false;
            else
                reset_lagswitch_pt1 = true;
            // désactiver le lagswitch
            lagcmd = "powershell \"Remove-NetQosPolicy -Name " + lag_rule_name + " -PolicyStore Activestore -confirm:$false\"";
            system(lagcmd.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

}

