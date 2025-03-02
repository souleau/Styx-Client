#include "Modules.h"
#include <ImGui/imgui.h>
#include <iostream>
#include "../../net/minecraft/network/Packet/Packet.h"
#include "../../net/minecraft/network/play/client/C03PacketPlayer/C03PacketPlayer.h"
#include <thread>
#include "../../net/minecraft/client/Minecraft/Minecraft.h"
#include "../Hook/JavaHook.h"
#include "../Cache/Cache.h"
#include <gl/GL.h>
#include "themered.h"

namespace Kisse {
    class ThemeManager {
    public:
        static ImGuiStyle GetDefaultStyle() {
            ImGuiStyle style;
            style.Alpha = 0.699999988079071f;
            style.DisabledAlpha = 1.0f;
            style.WindowPadding = ImVec2(11.30000019073486f, 11.0f);
            style.WindowRounding = 0.0f;
            style.WindowBorderSize = 1.0f;
            style.WindowMinSize = ImVec2(32.0f, 32.0f);
            style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
            style.WindowMenuButtonPosition = ImGuiDir_Left;
            style.ChildRounding = 0.0f;
            style.ChildBorderSize = 1.0f;
            style.PopupRounding = 0.0f;
            style.PopupBorderSize = 1.0f;
            style.FramePadding = ImVec2(4.800000190734863f, 4.300000190734863f);
            style.FrameRounding = 0.0f;
            style.FrameBorderSize = 0.0f;
            style.ItemSpacing = ImVec2(8.0f, 4.0f);
            style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
            style.CellPadding = ImVec2(7.900000095367432f, 5.300000190734863f);
            style.IndentSpacing = 21.0f;
            style.ColumnsMinSpacing = 6.0f;
            style.ScrollbarSize = 20.0f;
            style.ScrollbarRounding = 0.0f;
            style.GrabMinSize = 13.0f;
            style.GrabRounding = 0.0f;
            style.TabRounding = 2.599999904632568f;
            style.TabBorderSize = 0.0f;
            style.TabMinWidthForCloseButton = 0.0f;
            style.ColorButtonPosition = ImGuiDir_None;
            style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
            style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

            style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08154505491256714f, 0.08154423534870148f, 0.08154423534870148f, 0.3390557765960693f);
            style.Colors[ImGuiCol_ChildBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
            style.Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.0784313753247261f, 0.0784313753247261f, 0.9399999976158142f);
            style.Colors[ImGuiCol_Border] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
            style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.5064377784729004f, 0.5064327120780945f, 0.5064327120780945f, 0.0f);
            style.Colors[ImGuiCol_FrameBg] = ImVec4(0.3090097904205322f, 0.3090114295482635f, 0.3090128898620605f, 0.5400000214576721f);
            style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.7682403326034546f, 0.7682326436042786f, 0.7682326436042786f, 0.4000000059604645f);
            style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.6609442234039307f, 0.6609376072883606f, 0.6609376072883606f, 0.6700000166893005f);
            style.Colors[ImGuiCol_TitleBg] = ImVec4(0.5836910009384155f, 0.5836851596832275f, 0.5836851596832275f, 1.0f);
            style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.6738197803497314f, 0.6738130450248718f, 0.6738130450248718f, 1.0f);
            style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(9.999999974752427e-07f, 9.999899930335232e-07f, 9.999899930335232e-07f, 0.3733905553817749f);
            style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
            style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.7854077219963074f, 0.785399854183197f, 0.785399854183197f, 1.0f);
            style.Colors[ImGuiCol_CheckMark] = ImVec4(0.7811158895492554f, 0.7811080813407898f, 0.7811080813407898f, 1.0f);
            style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.6308949589729309f, 0.6309012770652771f, 0.6308949589729309f, 1.0f);
            style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.7124463319778442f, 0.7124391794204712f, 0.7124391794204712f, 1.0f);
            style.Colors[ImGuiCol_Button] = ImVec4(0.4392156898975372f, 0.4392156898975372f, 0.4392156898975372f, 0.4000000059604645f);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4588235318660736f, 0.4666666686534882f, 0.47843137383461f, 1.0f);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.4196078479290009f, 0.4196078479290009f, 0.4196078479290009f, 1.0f);
            style.Colors[ImGuiCol_Header] = ImVec4(0.6980392336845398f, 0.6980392336845398f, 0.6980392336845398f, 0.3100000023841858f);
            style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.6980392336845398f, 0.6980392336845398f, 0.6980392336845398f, 0.800000011920929f);
            style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.47843137383461f, 0.4980392158031464f, 0.5176470875740051f, 1.0f);
            style.Colors[ImGuiCol_Separator] = ImVec4(0.7467736601829529f, 0.7467736601829529f, 0.7467811107635498f, 0.5f);
            style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.7176470756530762f, 0.7176470756530762f, 0.7176470756530762f, 0.7799999713897705f);
            style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
            style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.9098039269447327f, 0.9098039269447327f, 0.9098039269447327f, 0.25f);
            style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.8078431487083435f, 0.8078431487083435f, 0.8078431487083435f, 0.6700000166893005f);
            style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.4588235318660736f, 0.4588235318660736f, 0.4588235318660736f, 0.949999988079071f);
            style.Colors[ImGuiCol_Tab] = ImVec4(0.168627455830574f, 0.1647058874368668f, 0.1607843190431595f, 1.0f);
            style.Colors[ImGuiCol_TabHovered] = ImVec4(0.6566521525382996f, 0.6566523313522339f, 0.6566457748413086f, 0.8627451062202454f);
            style.Colors[ImGuiCol_TabActive] = ImVec4(0.6523605585098267f, 0.6523605585098267f, 0.6523540019989014f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.168627455830574f, 0.1647058874368668f, 0.1607843190431595f, 1.0f);
            style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.168627455830574f, 0.1647058874368668f, 0.1607843190431595f, 1.0f);
            style.Colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
            style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
            style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.0f, 0.9527896642684937f, 0.0f, 0.1630901098251343f);
            style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.9999960064888f, 0.9999899864196777f, 1.0f);
            style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
            style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
            style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
            style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
            style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
            style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.8666666746139526f, 0.8666666746139526f, 0.8666666746139526f, 0.3499999940395355f);
            style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
            style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6000000238418579f, 1.0f);
            style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
            style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
            style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
            return style;
        }



        static void ApplyDefaultTheme() {
            ImGui::GetStyle() = GetDefaultStyle();
        }


        static void ApplyRedTheme() {
            ImGui::GetStyle() = GetRedStyle();
        }

        static void ApplyDarkTheme() {
            ImGui::StyleColorsDark();
        }

        static void ApplyLightTheme() {
            ImGui::StyleColorsLight();
        }

        static void ApplyClassicTheme() {
            ImGui::StyleColorsClassic();
        }
    };

    void Modules::Theme::renderGUI() {

        static const char* themes[] = { "Default", "Classic", "Blue", "Light", "Red" };
        static int selected_theme = 0;

        if (ImGui::Combo("Theme", &selected_theme, themes, IM_ARRAYSIZE(themes))) {
            switch (selected_theme) {
            case 0:
                ThemeManager::ApplyDefaultTheme();
                break;
            case 1:
                ThemeManager::ApplyClassicTheme();
                break;
            case 2:
                ThemeManager::ApplyDarkTheme();
                break;
            case 3:
                ThemeManager::ApplyLightTheme();
                break;
            case 4:
                ThemeManager::ApplyRedTheme();
                break;
            }
        }
    }
}
