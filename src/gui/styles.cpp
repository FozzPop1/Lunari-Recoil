#include "../../inc/gui/styles.h"

#include "../../ext/inc/Imgui/imgui.h"

void DefualtDarkStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // ── Layout ───────────────────────────────────────────────────────────────
    style.Alpha                  = 1.0f;
    style.DisabledAlpha          = 0.4f;
    style.WindowPadding          = ImVec2(16.0f, 16.0f);
    style.WindowRounding         = 8.0f;
    style.WindowBorderSize       = 1.0f;
    style.WindowMinSize          = ImVec2(20.0f, 20.0f);
    style.WindowTitleAlign       = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildRounding          = 6.0f;
    style.ChildBorderSize        = 1.0f;
    style.PopupRounding          = 8.0f;
    style.PopupBorderSize        = 1.0f;
    style.FramePadding           = ImVec2(12.0f, 6.0f);
    style.FrameRounding          = 5.0f;
    style.FrameBorderSize        = 0.0f;
    style.ItemSpacing            = ImVec2(8.0f, 6.0f);
    style.ItemInnerSpacing       = ImVec2(6.0f, 6.0f);
    style.CellPadding            = ImVec2(8.0f, 4.0f);
    style.IndentSpacing          = 18.0f;
    style.ColumnsMinSpacing      = 6.0f;
    style.ScrollbarSize          = 10.0f;
    style.ScrollbarRounding      = 99.0f; // pill
    style.GrabMinSize            = 10.0f;
    style.GrabRounding           = 99.0f; // pill
    style.TabRounding            = 6.0f;
    style.TabBorderSize          = 0.0f;
    style.ColorButtonPosition    = ImGuiDir_Right;
    style.ButtonTextAlign        = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign    = ImVec2(0.0f, 0.5f);

    // ── Palette ──────────────────────────────────────────────────────────────
    // Base surfaces
    // bg0  = #08090d  deepest background
    // bg1  = #0d0e14  window bg
    // bg2  = #11121a  child / popup bg
    // bg3  = #191a24  elevated / frame
    // bg4  = #21222e  hovered frame
    // line = #2a2b38  borders
    // mute = #4a4b60  disabled / muted text
    // text = #e8e9f0  primary text
    // acc  = #7b68ee  accent (medium slate purple)
    // accH = #9b8fff  accent hovered
    // accA = #5a4ed4  accent active / pressed

    ImVec4* c = style.Colors;

    c[ImGuiCol_Text]                  = ImVec4(0.910f, 0.914f, 0.941f, 1.00f);
    c[ImGuiCol_TextDisabled]          = ImVec4(0.290f, 0.294f, 0.376f, 1.00f);

    c[ImGuiCol_WindowBg]              = ImVec4(0.051f, 0.055f, 0.078f, 0.92f);
    c[ImGuiCol_ChildBg]               = ImVec4(0.067f, 0.071f, 0.102f, 1.00f);
    c[ImGuiCol_PopupBg]               = ImVec4(0.067f, 0.071f, 0.102f, 1.00f);

    c[ImGuiCol_Border]                = ImVec4(0.165f, 0.169f, 0.220f, 1.00f);
    c[ImGuiCol_BorderShadow]          = ImVec4(0.000f, 0.000f, 0.000f, 0.00f);

	c[ImGuiCol_FrameBg]        = ImVec4(0.098f, 0.102f, 0.141f, 1.00f);
	c[ImGuiCol_FrameBgHovered] = ImVec4(0.098f, 0.102f, 0.141f, 1.00f);
	c[ImGuiCol_FrameBgActive]  = ImVec4(0.098f, 0.102f, 0.141f, 1.00f);

    c[ImGuiCol_TitleBg]               = ImVec4(0.039f, 0.043f, 0.063f, 1.00f);
    c[ImGuiCol_TitleBgActive]         = ImVec4(0.051f, 0.055f, 0.082f, 1.00f);
    c[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.039f, 0.043f, 0.063f, 1.00f);

    c[ImGuiCol_MenuBarBg]             = ImVec4(0.039f, 0.043f, 0.063f, 1.00f);

    c[ImGuiCol_ScrollbarBg]           = ImVec4(0.039f, 0.043f, 0.063f, 0.00f);
    c[ImGuiCol_ScrollbarGrab]         = ImVec4(0.165f, 0.169f, 0.220f, 1.00f);
    c[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.482f, 0.408f, 0.933f, 1.00f);
    c[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.353f, 0.306f, 0.831f, 1.00f);

    c[ImGuiCol_CheckMark]             = ImVec4(0.482f, 0.408f, 0.933f, 1.00f);

    c[ImGuiCol_SliderGrab]            = ImVec4(0.482f, 0.408f, 0.933f, 1.00f);
    c[ImGuiCol_SliderGrabActive]      = ImVec4(0.612f, 0.561f, 1.000f, 1.00f);

	c[ImGuiCol_Button]        		  = ImVec4(0.098f, 0.102f, 0.141f, 1.00f);
	c[ImGuiCol_ButtonHovered]         = ImVec4(0.482f, 0.408f, 0.933f, 0.15f);
	c[ImGuiCol_ButtonActive]  = ImVec4(0.220f, 0.200f, 0.320f, 1.00f);
    
	c[ImGuiCol_Header]                = ImVec4(0.482f, 0.408f, 0.933f, 0.15f);
    c[ImGuiCol_HeaderHovered]         = ImVec4(0.482f, 0.408f, 0.933f, 0.25f);
    c[ImGuiCol_HeaderActive]          = ImVec4(0.482f, 0.408f, 0.933f, 0.35f);

    c[ImGuiCol_Separator]             = ImVec4(0.165f, 0.169f, 0.220f, 1.00f);
    c[ImGuiCol_SeparatorHovered]      = ImVec4(0.482f, 0.408f, 0.933f, 0.60f);
    c[ImGuiCol_SeparatorActive]       = ImVec4(0.482f, 0.408f, 0.933f, 1.00f);

    c[ImGuiCol_ResizeGrip]            = ImVec4(0.482f, 0.408f, 0.933f, 0.12f);
    c[ImGuiCol_ResizeGripHovered]     = ImVec4(0.482f, 0.408f, 0.933f, 0.60f);
    c[ImGuiCol_ResizeGripActive]      = ImVec4(0.482f, 0.408f, 0.933f, 0.90f);

    c[ImGuiCol_Tab]                   = ImVec4(0.067f, 0.071f, 0.102f, 1.00f);
    c[ImGuiCol_TabHovered]            = ImVec4(0.482f, 0.408f, 0.933f, 0.20f);
    c[ImGuiCol_TabActive]             = ImVec4(0.482f, 0.408f, 0.933f, 0.30f);
    c[ImGuiCol_TabUnfocused]          = ImVec4(0.067f, 0.071f, 0.102f, 1.00f);
    c[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.098f, 0.102f, 0.141f, 1.00f);

    c[ImGuiCol_PlotLines]             = ImVec4(0.482f, 0.408f, 0.933f, 1.00f);
    c[ImGuiCol_PlotLinesHovered]      = ImVec4(0.612f, 0.561f, 1.000f, 1.00f);
    c[ImGuiCol_PlotHistogram]         = ImVec4(0.482f, 0.408f, 0.933f, 1.00f);
    c[ImGuiCol_PlotHistogramHovered]  = ImVec4(0.612f, 0.561f, 1.000f, 1.00f);

    c[ImGuiCol_TableHeaderBg]         = ImVec4(0.067f, 0.071f, 0.102f, 1.00f);
    c[ImGuiCol_TableBorderStrong]     = ImVec4(0.165f, 0.169f, 0.220f, 1.00f);
    c[ImGuiCol_TableBorderLight]      = ImVec4(0.110f, 0.114f, 0.157f, 1.00f);
    c[ImGuiCol_TableRowBg]            = ImVec4(0.000f, 0.000f, 0.000f, 0.00f);
    c[ImGuiCol_TableRowBgAlt]         = ImVec4(1.000f, 1.000f, 1.000f, 0.03f);

    c[ImGuiCol_TextSelectedBg]        = ImVec4(0.482f, 0.408f, 0.933f, 0.25f);
    c[ImGuiCol_DragDropTarget]        = ImVec4(0.482f, 0.408f, 0.933f, 0.90f);
    c[ImGuiCol_NavHighlight]          = ImVec4(0.482f, 0.408f, 0.933f, 0.80f);
    c[ImGuiCol_NavWindowingHighlight] = ImVec4(0.482f, 0.408f, 0.933f, 0.70f);
    c[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.000f, 0.000f, 0.000f, 0.40f);
    c[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.000f, 0.000f, 0.000f, 0.50f);

	c[ImGuiCol_CheckboxSelectedBg] = ImVec4(0.098f, 0.102f, 0.141f, 1.00f);
}

void DefualtLightStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // ── Layout (same structure as dark, slightly brighter feel) ───────────────
    style.Alpha                     = 1.0f;
    style.DisabledAlpha             = 0.5f;
    style.WindowPadding             = ImVec2(16.0f, 16.0f);
    style.WindowRounding            = 8.0f;
    style.WindowBorderSize          = 1.0f;
    style.ChildRounding             = 6.0f;
    style.PopupRounding             = 8.0f;
    style.FramePadding              = ImVec2(12.0f, 6.0f);
    style.FrameRounding             = 5.0f;
    style.ItemSpacing               = ImVec2(8.0f, 6.0f);
    style.ItemInnerSpacing          = ImVec2(6.0f, 6.0f);
    style.ScrollbarRounding         = 99.0f;
    style.GrabRounding              = 99.0f;
    style.TabRounding               = 6.0f;
    style.TabBorderSize             = 0.0f;
    style.ButtonTextAlign           = ImVec2(0.5f, 0.5f);

    ImVec4* c = style.Colors;

    // ── Core ────────────────────────────────────────────────────────────────
    c[ImGuiCol_Text]                 = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
    c[ImGuiCol_TextDisabled]         = ImVec4(0.50f, 0.50f, 0.55f, 1.00f);

    c[ImGuiCol_WindowBg]             = ImVec4(0.96f, 0.97f, 0.99f, 0.95f);
    c[ImGuiCol_ChildBg]              = ImVec4(0.93f, 0.94f, 0.97f, 1.00f);
    c[ImGuiCol_PopupBg]              = ImVec4(0.96f, 0.97f, 0.99f, 1.00f);

    c[ImGuiCol_Border]               = ImVec4(0.85f, 0.86f, 0.90f, 1.00f);
    c[ImGuiCol_BorderShadow]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // ── Frames ─────────────────────────────────────────────────────────────
    c[ImGuiCol_FrameBg]              = ImVec4(0.90f, 0.91f, 0.94f, 1.00f);
    c[ImGuiCol_FrameBgHovered]       = ImVec4(0.87f, 0.88f, 0.92f, 1.00f);
    c[ImGuiCol_FrameBgActive]        = ImVec4(0.85f, 0.86f, 0.90f, 1.00f);

    // ── Title ──────────────────────────────────────────────────────────────
    c[ImGuiCol_TitleBg]              = ImVec4(0.94f, 0.95f, 0.98f, 1.00f);
    c[ImGuiCol_TitleBgActive]        = ImVec4(0.92f, 0.93f, 0.97f, 1.00f);
    c[ImGuiCol_TitleBgCollapsed]     = ImVec4(0.94f, 0.95f, 0.98f, 1.00f);

    // ── Buttons (keep your purple accent) ──────────────────────────────────
    c[ImGuiCol_Button]               = ImVec4(0.90f, 0.91f, 0.94f, 1.00f);
    c[ImGuiCol_ButtonHovered]        = ImVec4(0.482f, 0.408f, 0.933f, 0.20f);
    c[ImGuiCol_ButtonActive]         = ImVec4(0.482f, 0.408f, 0.933f, 0.30f);

    // ── Headers ────────────────────────────────────────────────────────────
    c[ImGuiCol_Header]               = ImVec4(0.482f, 0.408f, 0.933f, 0.15f);
    c[ImGuiCol_HeaderHovered]        = ImVec4(0.482f, 0.408f, 0.933f, 0.25f);
    c[ImGuiCol_HeaderActive]         = ImVec4(0.482f, 0.408f, 0.933f, 0.35f);

    // ── Scrollbar ──────────────────────────────────────────────────────────
    c[ImGuiCol_ScrollbarBg]          = ImVec4(0.95f, 0.95f, 0.97f, 0.00f);
    c[ImGuiCol_ScrollbarGrab]        = ImVec4(0.80f, 0.80f, 0.85f, 1.00f);
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.482f, 0.408f, 0.933f, 0.25f);
    c[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.482f, 0.408f, 0.933f, 0.35f);

    // ── Accent ─────────────────────────────────────────────────────────────
    c[ImGuiCol_CheckMark]            = ImVec4(0.482f, 0.408f, 0.933f, 1.00f);
    c[ImGuiCol_SliderGrab]           = ImVec4(0.482f, 0.408f, 0.933f, 1.00f);
    c[ImGuiCol_SliderGrabActive]     = ImVec4(0.612f, 0.561f, 1.000f, 1.00f);

    // ── Tabs ───────────────────────────────────────────────────────────────
    c[ImGuiCol_Tab]                  = ImVec4(0.92f, 0.93f, 0.96f, 1.00f);
    c[ImGuiCol_TabHovered]           = ImVec4(0.482f, 0.408f, 0.933f, 0.20f);
    c[ImGuiCol_TabActive]            = ImVec4(0.90f, 0.91f, 0.95f, 1.00f);

    // ── Misc ───────────────────────────────────────────────────────────────
    c[ImGuiCol_Separator]            = ImVec4(0.85f, 0.86f, 0.90f, 1.00f);
    c[ImGuiCol_TextSelectedBg]       = ImVec4(0.482f, 0.408f, 0.933f, 0.25f);
    c[ImGuiCol_NavHighlight]         = ImVec4(0.482f, 0.408f, 0.933f, 0.70f);
}

void DefualtDarkPurpleStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // ── Layout (match your light style structure) ──────────────────────────
    style.Alpha                     = 1.0f;
    style.DisabledAlpha             = 0.5f;
    style.WindowPadding             = ImVec2(16.0f, 16.0f);
    style.WindowRounding            = 8.0f;
    style.WindowBorderSize          = 1.0f;
    style.ChildRounding             = 6.0f;
    style.PopupRounding             = 8.0f;
    style.FramePadding              = ImVec2(12.0f, 6.0f);
    style.FrameRounding             = 5.0f;
    style.ItemSpacing               = ImVec2(8.0f, 6.0f);
    style.ItemInnerSpacing          = ImVec2(6.0f, 6.0f);
    style.ScrollbarRounding         = 99.0f;
    style.GrabRounding              = 99.0f;
    style.TabRounding               = 6.0f;
    style.TabBorderSize             = 0.0f;
    style.ButtonTextAlign           = ImVec2(0.5f, 0.5f);

    ImVec4* c = style.Colors;

    // ── Core ───────────────────────────────────────────────────────────────
    c[ImGuiCol_Text]                 = ImVec4(0.91f, 0.914f, 0.941f, 1.0f);
    c[ImGuiCol_TextDisabled]         = ImVec4(0.55f, 0.56f, 0.62f, 1.0f);

    c[ImGuiCol_WindowBg]             = ImVec4(0.05f, 0.055f, 0.078f, 0.98f);
    c[ImGuiCol_ChildBg]              = ImVec4(0.07f, 0.071f, 0.102f, 1.0f);
    c[ImGuiCol_PopupBg]              = ImVec4(0.06f, 0.065f, 0.090f, 1.0f);

    c[ImGuiCol_Border]               = ImVec4(0.14f, 0.14f, 0.18f, 1.0f);
    c[ImGuiCol_BorderShadow]         = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    // ── Frames ─────────────────────────────────────────────────────────────
    c[ImGuiCol_FrameBg]              = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
    c[ImGuiCol_FrameBgHovered]       = ImVec4(0.13f, 0.12f, 0.18f, 1.0f);
    c[ImGuiCol_FrameBgActive]        = ImVec4(0.15f, 0.14f, 0.22f, 1.0f);

    // ── Title ──────────────────────────────────────────────────────────────
    c[ImGuiCol_TitleBg]              = ImVec4(0.05f, 0.055f, 0.078f, 1.0f);
    c[ImGuiCol_TitleBgActive]        = ImVec4(0.07f, 0.071f, 0.102f, 1.0f);
    c[ImGuiCol_TitleBgCollapsed]     = ImVec4(0.05f, 0.055f, 0.078f, 1.0f);

    // ── Buttons (DARK purple accent, not washed out) ───────────────────────
    c[ImGuiCol_Button]               = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
    c[ImGuiCol_ButtonHovered]        = ImVec4(0.45f, 0.38f, 0.90f, 0.35f);
    c[ImGuiCol_ButtonActive]         = ImVec4(0.45f, 0.38f, 0.90f, 0.50f);

    // ── Headers ────────────────────────────────────────────────────────────
    c[ImGuiCol_Header]               = ImVec4(0.45f, 0.38f, 0.90f, 0.20f);
    c[ImGuiCol_HeaderHovered]        = ImVec4(0.45f, 0.38f, 0.90f, 0.30f);
    c[ImGuiCol_HeaderActive]         = ImVec4(0.45f, 0.38f, 0.90f, 0.45f);

    // ── Scrollbar ──────────────────────────────────────────────────────────
    c[ImGuiCol_ScrollbarBg]          = ImVec4(0.03f, 0.03f, 0.05f, 0.0f);
    c[ImGuiCol_ScrollbarGrab]        = ImVec4(0.20f, 0.20f, 0.25f, 1.0f);
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.45f, 0.38f, 0.90f, 0.35f);
    c[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.45f, 0.38f, 0.90f, 0.50f);

    // ── Accent (THIS is the key fix: darker + more solid purple) ───────────
    c[ImGuiCol_CheckMark]            = ImVec4(0.45f, 0.38f, 0.90f, 1.0f);
    c[ImGuiCol_SliderGrab]           = ImVec4(0.45f, 0.38f, 0.90f, 1.0f);
    c[ImGuiCol_SliderGrabActive]     = ImVec4(0.55f, 0.48f, 1.00f, 1.0f);

    // ── Tabs ───────────────────────────────────────────────────────────────
    c[ImGuiCol_Tab]                  = ImVec4(0.07f, 0.07f, 0.10f, 1.0f);
    c[ImGuiCol_TabHovered]           = ImVec4(0.45f, 0.38f, 0.90f, 0.25f);
    c[ImGuiCol_TabActive]            = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);

    // ── Misc ───────────────────────────────────────────────────────────────
    c[ImGuiCol_Separator]            = ImVec4(0.14f, 0.14f, 0.18f, 1.0f);
    c[ImGuiCol_TextSelectedBg]       = ImVec4(0.45f, 0.38f, 0.90f, 0.25f);
    c[ImGuiCol_NavHighlight]         = ImVec4(0.45f, 0.38f, 0.90f, 0.70f);
}

void DefaultDarkBlueStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.5f;
    style.WindowPadding = ImVec2(16, 16);
    style.WindowRounding = 8.0f;
    style.WindowBorderSize = 1.0f;
    style.ChildRounding = 6.0f;
    style.PopupRounding = 8.0f;
    style.FramePadding = ImVec2(12, 6);
    style.FrameRounding = 5.0f;
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.ScrollbarRounding = 99.0f;
    style.GrabRounding = 99.0f;
    style.TabRounding = 6.0f;
    style.TabBorderSize = 0.0f;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

    ImVec4* c = style.Colors;

    ImVec4 accent = ImVec4(0.20f, 0.55f, 0.95f, 1.0f); // blue

    c[ImGuiCol_Text] = ImVec4(0.91f, 0.914f, 0.941f, 1.0f);
    c[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.055f, 0.078f, 0.98f);
    c[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.071f, 0.102f, 1.0f);
    c[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.065f, 0.090f, 1.0f);

    c[ImGuiCol_Border] = ImVec4(0.14f, 0.14f, 0.18f, 1.0f);

    c[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
    c[ImGuiCol_FrameBgHovered] = ImVec4(0.13f, 0.12f, 0.18f, 1.0f);
    c[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.14f, 0.22f, 1.0f);

    c[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.055f, 0.078f, 1.0f);
    c[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.071f, 0.102f, 1.0f);

    c[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
    c[ImGuiCol_ButtonHovered] = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    c[ImGuiCol_ButtonActive] = ImVec4(accent.x, accent.y, accent.z, 0.50f);

    c[ImGuiCol_Header] = ImVec4(accent.x, accent.y, accent.z, 0.20f);
    c[ImGuiCol_HeaderHovered] = ImVec4(accent.x, accent.y, accent.z, 0.30f);
    c[ImGuiCol_HeaderActive] = ImVec4(accent.x, accent.y, accent.z, 0.45f);

    c[ImGuiCol_CheckMark] = accent;
    c[ImGuiCol_SliderGrab] = accent;
    c[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.70f, 1.0f, 1.0f);

    c[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.10f, 1.0f);
    c[ImGuiCol_TabHovered] = ImVec4(accent.x, accent.y, accent.z, 0.25f);
    c[ImGuiCol_TabActive] = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
}

void DefaultDarkGreenStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 0.5f;
    style.WindowPadding = ImVec2(16, 16);
    style.WindowRounding = 8.0f;
    style.WindowBorderSize = 1.0f;
    style.ChildRounding = 6.0f;
    style.PopupRounding = 8.0f;
    style.FramePadding = ImVec2(12, 6);
    style.FrameRounding = 5.0f;
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.ScrollbarRounding = 99.0f;
    style.GrabRounding = 99.0f;
    style.TabRounding = 6.0f;
    style.TabBorderSize = 0.0f;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

    ImVec4* c = style.Colors;

    ImVec4 accent = ImVec4(0.20f, 0.85f, 0.45f, 1.0f); // green

    c[ImGuiCol_Text] = ImVec4(0.91f, 0.914f, 0.941f, 1.0f);
    c[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.055f, 0.078f, 0.98f);
    c[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.071f, 0.102f, 1.0f);
    c[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.065f, 0.090f, 1.0f);

    c[ImGuiCol_Border] = ImVec4(0.14f, 0.14f, 0.18f, 1.0f);

    c[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
    c[ImGuiCol_FrameBgHovered] = ImVec4(0.13f, 0.12f, 0.18f, 1.0f);
    c[ImGuiCol_FrameBgActive] = ImVec4(0.15f, 0.14f, 0.22f, 1.0f);

    c[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.055f, 0.078f, 1.0f);
    c[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.071f, 0.102f, 1.0f);

    c[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
    c[ImGuiCol_ButtonHovered] = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    c[ImGuiCol_ButtonActive] = ImVec4(accent.x, accent.y, accent.z, 0.50f);

    c[ImGuiCol_Header] = ImVec4(accent.x, accent.y, accent.z, 0.20f);
    c[ImGuiCol_HeaderHovered] = ImVec4(accent.x, accent.y, accent.z, 0.30f);
    c[ImGuiCol_HeaderActive] = ImVec4(accent.x, accent.y, accent.z, 0.45f);

    c[ImGuiCol_CheckMark] = accent;
    c[ImGuiCol_SliderGrab] = accent;
    c[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 1.0f, 0.60f, 1.0f);

    c[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.10f, 1.0f);
    c[ImGuiCol_TabHovered] = ImVec4(accent.x, accent.y, accent.z, 0.25f);
    c[ImGuiCol_TabActive] = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
}