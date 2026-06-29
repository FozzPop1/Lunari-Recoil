#include "../../inc/gui/styles.h"

#include "../../ext/inc/Imgui/imgui.h"

void DefualtDarkStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // ── Layout (clean + modern spacing) ──────────────────────────────────────
    style.Alpha                    = 1.0f;
    style.DisabledAlpha            = 0.45f;

    style.WindowPadding            = ImVec2(14.0f, 14.0f);
    style.WindowRounding           = 8.0f;
    style.WindowBorderSize         = 0.0f;
    style.WindowMinSize            = ImVec2(24.0f, 24.0f);
    style.WindowTitleAlign         = ImVec2(0.0f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_None;

    style.ChildRounding            = 7.0f;
    style.ChildBorderSize          = 1.0f;

    style.PopupRounding            = 8.0f;
    style.PopupBorderSize          = 1.0f;

    style.FramePadding             = ImVec2(10.0f, 6.0f);
    style.FrameRounding            = 6.0f;
    style.FrameBorderSize          = 0.0f;

    style.ItemSpacing              = ImVec2(8.0f, 7.0f);
    style.ItemInnerSpacing         = ImVec2(6.0f, 5.0f);

    style.CellPadding              = ImVec2(8.0f, 4.0f);
    style.IndentSpacing            = 16.0f;

    style.ScrollbarSize            = 10.0f;
    style.ScrollbarRounding        = 100.0f;

    style.GrabMinSize              = 10.0f;
    style.GrabRounding             = 100.0f;

    style.TabRounding              = 6.0f;
    style.TabBorderSize            = 0.0f;

    style.ButtonTextAlign          = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign      = ImVec2(0.0f, 0.5f);

    // ── CLEAN SPACE COLOR PALETTE ────────────────────────────────────────────
    // Backgrounds (neutral graphite, no purple tint)
    const ImVec4 bg0 = ImVec4(0.040f, 0.043f, 0.055f, 1.00f);
    const ImVec4 bg1 = ImVec4(0.055f, 0.058f, 0.075f, 1.00f);
    const ImVec4 bg2 = ImVec4(0.070f, 0.074f, 0.095f, 1.00f);
    const ImVec4 bg3 = ImVec4(0.095f, 0.100f, 0.125f, 1.00f);

    // Borders (soft, not harsh)
    const ImVec4 border = ImVec4(0.160f, 0.165f, 0.200f, 1.00f);

    // Text (slightly soft white)
    const ImVec4 text       = ImVec4(0.92f, 0.93f, 0.96f, 1.00f);
    const ImVec4 textMuted  = ImVec4(0.45f, 0.47f, 0.55f, 1.00f);

    // Accent (clean BLUE — no purple)
    const ImVec4 accent     = ImVec4(0.25f, 0.55f, 1.00f, 1.00f);
    const ImVec4 accentH    = ImVec4(0.40f, 0.68f, 1.00f, 1.00f);
    const ImVec4 accentA    = ImVec4(0.18f, 0.42f, 0.85f, 1.00f);

    ImVec4* c = style.Colors;

    // ── Core UI ──────────────────────────────────────────────────────────────
    c[ImGuiCol_Text]              = text;
    c[ImGuiCol_TextDisabled]      = textMuted;

    c[ImGuiCol_WindowBg]          = bg0;
    c[ImGuiCol_ChildBg]           = ImVec4(0, 0, 0, 0.3f);
    c[ImGuiCol_PopupBg]           = bg1;

    c[ImGuiCol_Border]            = border;
    c[ImGuiCol_BorderShadow]      = ImVec4(0, 0, 0, 0);

    // ── Frames (clean flat look) ────────────────────────────────────────────
    c[ImGuiCol_FrameBg]           = bg2;
    c[ImGuiCol_FrameBgHovered]    = bg3;
    c[ImGuiCol_FrameBgActive]     = bg3;

    // ── Title ────────────────────────────────────────────────────────────────
    c[ImGuiCol_TitleBg]           = bg0;
    c[ImGuiCol_TitleBgActive]     = bg1;
    c[ImGuiCol_TitleBgCollapsed]  = bg0;

    c[ImGuiCol_MenuBarBg]         = bg0;

    // ── Scrollbar (subtle accent hint only on hover) ────────────────────────
    c[ImGuiCol_ScrollbarBg]       = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_ScrollbarGrab]     = border;
    c[ImGuiCol_ScrollbarGrabHovered] = accent;
    c[ImGuiCol_ScrollbarGrabActive]   = accentA;

    // ── Accent Controls ─────────────────────────────────────────────────────
    c[ImGuiCol_CheckMark]         = accent;

    c[ImGuiCol_SliderGrab]        = accent;
    c[ImGuiCol_SliderGrabActive]  = accentH;

    // ── Buttons (clean + minimal feedback) ───────────────────────────────────
    c[ImGuiCol_Button]            = bg2;
    c[ImGuiCol_ButtonHovered]     = ImVec4(0.12f, 0.25f, 0.45f, 1.00f);
    c[ImGuiCol_ButtonActive]      = accentA;

    // ── Headers (very clean highlight system) ───────────────────────────────
    c[ImGuiCol_Header]            = ImVec4(accent.x, accent.y, accent.z, 0.12f);
    c[ImGuiCol_HeaderHovered]     = ImVec4(accent.x, accent.y, accent.z, 0.20f);
    c[ImGuiCol_HeaderActive]      = ImVec4(accent.x, accent.y, accent.z, 0.30f);

    // ── Separators ──────────────────────────────────────────────────────────
    c[ImGuiCol_Separator]         = border;
    c[ImGuiCol_SeparatorHovered]  = accent;
    c[ImGuiCol_SeparatorActive]   = accentH;

    // ── Resize Grip ─────────────────────────────────────────────────────────
    c[ImGuiCol_ResizeGrip]        = ImVec4(accent.x, accent.y, accent.z, 0.10f);
    c[ImGuiCol_ResizeGripHovered] = ImVec4(accent.x, accent.y, accent.z, 0.35f);
    c[ImGuiCol_ResizeGripActive]  = ImVec4(accent.x, accent.y, accent.z, 0.55f);

    // ── Tabs (very clean system) ────────────────────────────────────────────
    c[ImGuiCol_Tab]               = bg1;
    c[ImGuiCol_TabHovered]        = ImVec4(accent.x, accent.y, accent.z, 0.20f);
    c[ImGuiCol_TabActive]         = ImVec4(accent.x, accent.y, accent.z, 0.30f);
    c[ImGuiCol_TabUnfocused]      = bg1;
    c[ImGuiCol_TabUnfocusedActive]= bg2;

    // ── Plots ────────────────────────────────────────────────────────────────
    c[ImGuiCol_PlotLines]         = accent;
    c[ImGuiCol_PlotLinesHovered]  = accentH;
    c[ImGuiCol_PlotHistogram]     = accent;
    c[ImGuiCol_PlotHistogramHovered] = accentH;

    // ── Tables ───────────────────────────────────────────────────────────────
    c[ImGuiCol_TableHeaderBg]     = bg1;
    c[ImGuiCol_TableBorderStrong] = border;
    c[ImGuiCol_TableBorderLight]  = ImVec4(0.10f, 0.11f, 0.14f, 1.0f);
    c[ImGuiCol_TableRowBg]        = ImVec4(0, 0, 0, 0);
    c[ImGuiCol_TableRowBgAlt]     = ImVec4(1, 1, 1, 0.02f);

    // ── Selection / Nav ─────────────────────────────────────────────────────
    c[ImGuiCol_TextSelectedBg]        = ImVec4(accent.x, accent.y, accent.z, 0.25f);
    c[ImGuiCol_DragDropTarget]        = accentH;
    c[ImGuiCol_NavHighlight]          = accent;
    c[ImGuiCol_NavWindowingHighlight] = accentH;
    c[ImGuiCol_NavWindowingDimBg]     = ImVec4(0, 0, 0, 0.35f);
    c[ImGuiCol_ModalWindowDimBg]      = ImVec4(0, 0, 0, 0.45f);
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