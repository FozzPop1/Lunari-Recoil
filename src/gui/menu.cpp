#include "../../inc/gui/menu.h"

#include "../../inc/macro/config.h"
#include "../../inc/macro/recoil.h"

#include "../../ext/inc/Imgui/imgui.h"
#include "../../ext/inc/Imgui/imgui_internal.h"
#include "../../inc/gui/background_effect.h"
#include "../../inc/version.h"
#include "../../inc/gui/window.h"

#include "../../resource/fonts/fontawesome6.h"

#include <filesystem>
#include <vector>
#include <string>
#include <cstring>

// ─────────────────────────────
// Globals
// ─────────────────────────────
ImVec2 MenuWindowPos;

bool ShowMenu = true;
bool RecoilToggle;

int menu_idx = 0;

char ConfigSaveName[256] = "user";

float MenuAlpha = 0.0f;
static float tabAnim[3] = { 0.0f, 0.0f, 0.0f };

// ─────────────────────────────
// Config helper
// ─────────────────────────────
std::vector<std::string> GetConfigFiles()
{
    std::vector<std::string> files;
    const std::filesystem::path path = "C:/Lunari/Recoil/Configs";

    std::error_code ec;
    if (!std::filesystem::exists(path, ec))
        return files;

    for (auto& p : std::filesystem::directory_iterator(path, ec))
        if (p.path().extension() == ".cfg")
            files.push_back(p.path().filename().string());

    return files;
}

// ─────────────────────────────
// Main Menu (single window)
// ─────────────────────────────
void Menu()
{
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, MenuAlpha);

    // Total width: sidebar(200) + main(800) + preview(200) = 1200
    ImGui::SetNextWindowSize(ImVec2(1200, 500));
    ImGui::Begin("Lunari Recoil Window", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar);

    MenuWindowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();

    RenderStarBackground(ImGui::GetWindowDrawList(),
        MenuWindowPos, windowSize, 0, MenuAlpha);

    // ─────────────────────────────
    // LEFT: Sidebar (200px)
    // ─────────────────────────────

    SidebarMenu();

    ImGui::SameLine();

    // ─────────────────────────────
    // CENTER: Tab content (800px)
    // ─────────────────────────────
    ImGui::BeginChild("##content", ImVec2(800, 0), false);

    ImGui::Spacing();

    // ── TAB: RECOIL ──

    RecoilMenu();

    // ── TAB: CONFIGS ──

    ConfigMenu();

    // ── TAB: SETTINGS ──

    SettingsMenu();

    ImGui::EndChild();

    ImGui::SameLine();

    // ─────────────────────────────
    // RIGHT: Preview (200px)
    // ─────────────────────────────
    ImGui::BeginChild("##preview", ImVec2(0, 0), false, ImGuiWindowFlags_NoInputs);

    ImGui::Text(" Preview");
    ImGui::Separator();

    ImVec2 childPos  = ImGui::GetWindowPos();
    ImVec2 childSize = ImGui::GetWindowSize();

    ImVec2 center(
        childPos.x + childSize.x * 0.5f,
        childPos.y + childSize.y * 0.5f
    );

    recoil.DrawMousePreview(
        ImGui::GetWindowDrawList(),
        center,
        config.RecoilX, config.RecoilY,
        config.SmoothingX, config.SmoothingY,
        config.Humanize, 60, MenuAlpha);

    ImGui::EndChild();

    ImGui::End();
    ImGui::PopStyleVar();
}