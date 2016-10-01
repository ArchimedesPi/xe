#include "theme.h"

#include <imgui.h>
#include <IconsMaterialDesign.h>

#include "services/locator.h"

using namespace services;

void setup_ui_theme(bool invert) {
    // -- set up fonts
    ImGuiIO& io = ImGui::GetIO();
    
    io.Fonts->Clear();

    // merge in MD and KG icons
    static const ImWchar md_icons_ranges[] = {ICON_MIN_MD, ICON_MAX_MD};
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;    
    //io.Fonts->AddFontFromFileTTF(find_resource("fonts/MaterialIcons-Regular.ttf").c_str(), 16.0f,  &icons_config, md_icons_ranges);

    // set up colors and styling
    ImGuiStyle * style = &ImGui::GetStyle();

    style->WindowPadding            = ImVec2(6, 6);
    style->WindowRounding           = 2.0f;
    style->ChildWindowRounding      = 3.0f;

    style->FramePadding             = ImVec2(3, 3);
    style->FrameRounding            = 2.0f;

    style->ItemSpacing              = ImVec2(6, 4);
    style->ItemInnerSpacing         = ImVec2(4, 4);
    style->TouchExtraPadding        = ImVec2(0, 0);

    style->IndentSpacing            = (ImGui::GetFontSize() + style->FramePadding.x*2);
    style->ScrollbarSize            = 15.0f;
    style->ScrollbarRounding        = 0.0f;

    style->GrabMinSize              = 5.0f;
    style->GrabRounding             = 2.0f;

    style->AntiAliasedLines = true;
    style->AntiAliasedShapes = true;

    style->Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled]          = ImVec4(0.29f, 0.28f, 0.28f, 0.90f);
    style->Colors[ImGuiCol_WindowBg]              = ImVec4(0.92f, 0.91f, 0.86f, 0.70f);
    style->Colors[ImGuiCol_ChildWindowBg]         = ImVec4(1.00f, 0.98f, 0.93f, 0.58f);
    style->Colors[ImGuiCol_PopupBg]               = ImVec4(0.92f, 0.91f, 0.88f, 0.92f);
    style->Colors[ImGuiCol_Border]                = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    style->Colors[ImGuiCol_BorderShadow]          = ImVec4(0.92f, 0.91f, 0.88f, 0.29f);
    style->Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.67f, 0.66f, 0.94f, 0.78f);
    style->Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.52f, 0.42f, 0.71f, 1.00f);
    style->Colors[ImGuiCol_TitleBg]               = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.45f, 0.32f, 0.71f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.92f, 0.91f, 0.86f, 0.70f);
    style->Colors[ImGuiCol_ScrollbarBg]           = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    style->Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.00f, 0.00f, 0.00f, 0.47f);
    style->Colors[ImGuiCol_ComboBg]               = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_CheckMark]             = ImVec4(0.52f, 0.42f, 0.71f, 1.00f);
    style->Colors[ImGuiCol_SliderGrab]            = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
    style->Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.00f, 0.00f, 0.00f, 0.47f);
    style->Colors[ImGuiCol_Button]                = ImVec4(0.45f, 0.32f, 0.71f, 0.68f);
    style->Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.45f, 0.32f, 0.71f, 0.78f);
    style->Colors[ImGuiCol_ButtonActive]          = ImVec4(0.45f, 0.32f, 0.71f, 1.00f);
    style->Colors[ImGuiCol_Header]                = ImVec4(0.45f, 0.32f, 0.71f, 0.68f);
    style->Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.45f, 0.32f, 0.71f, 0.78f);
    style->Colors[ImGuiCol_HeaderActive]          = ImVec4(0.45f, 0.32f, 0.71f, 1.00f);
    style->Colors[ImGuiCol_Column]                = ImVec4(0.00f, 0.00f, 0.00f, 0.29f);
    style->Colors[ImGuiCol_ColumnHovered]         = ImVec4(0.00f, 0.00f, 0.00f, 0.44f);
    style->Colors[ImGuiCol_ColumnActive]          = ImVec4(0.00f, 0.00f, 0.00f, 0.76f);
    style->Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
    style->Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
    style->Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.00f, 0.00f, 0.00f, 0.49f);
    style->Colors[ImGuiCol_CloseButton]           = ImVec4(0.00f, 0.00f, 0.00f, 0.32f);
    style->Colors[ImGuiCol_CloseButtonHovered]    = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
    style->Colors[ImGuiCol_CloseButtonActive]     = ImVec4(0.00f, 0.00f, 0.00f, 0.55f);
    style->Colors[ImGuiCol_PlotLines]             = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(0.45f, 0.00f, 1.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.00f, 0.00f, 0.00f, 0.67f);
    style->Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.45f, 0.00f, 1.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.67f, 0.66f, 0.94f, 0.78f);
    style->Colors[ImGuiCol_ModalWindowDarkening]  = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

    if (invert) {
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            ImVec4& col = style->Colors[i];
            float H, S, V;
            ImGui::ColorConvertRGBtoHSV( col.x, col.y, col.z, H, S, V );
            if( S < 0.1f )  { V = 1.0 - V; }
            ImGui::ColorConvertHSVtoRGB( H, S, V, col.x, col.y, col.z );
        }
    }
}

