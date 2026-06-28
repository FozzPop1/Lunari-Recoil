#include "../../inc/gui/menu.h"

#include "../../inc/macro/config.h"
#include "../../inc/macro/recoil.h"

#include "../../ext/inc/Imgui/imgui.h"
#include "../../ext/inc/Imgui/imgui_internal.h"
#include "../../inc/gui/background_effect.h"
#include "../../inc/version.h"
#include "../../inc/gui/window.h"

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
char ConfigLoadName[256] = { 0 };

float MenuAlpha = 0.0f;
static float tabAnim[3] = { 0.0f, 0.0f, 0.0f };

// ─────────────────────────────
// CLEAN ACCENT SYSTEM
// ─────────────────────────────
static const ImVec4 ACCENT        = ImVec4(0.25f, 0.55f, 1.00f, 1.0f);
static const ImVec4 ACCENT_HOVER  = ImVec4(0.40f, 0.70f, 1.00f, 1.0f);
static const ImVec4 BASE_BG       = ImVec4(0.06f, 0.07f, 0.09f, 1.0f);
static const ImVec4 BASE_SURFACE  = ImVec4(0.09f, 0.10f, 0.13f, 1.0f);

static const char* tabs[] = { "Recoil", "Configs", "Settings" };

// ─────────────────────────────
// Sidebar
// ─────────────────────────────
void Sidebar()
{
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, MenuAlpha);

    ImGui::SetNextWindowSize(ImVec2(200, 500));
    ImGui::SetNextWindowPos(ImVec2(MenuWindowPos.x - 200, MenuWindowPos.y));

    ImGui::Begin("Lunari Recoil", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar
    );

    RenderStarBackground(ImGui::GetWindowDrawList(),
        ImGui::GetWindowPos(),
        ImGui::GetWindowSize(),
        0);

    ImGui::Spacing();

    for (int i = 0; i < 3; i++)
    {
        bool active = (menu_idx == i);

        float target = active ? 1.0f : 0.0f;
        tabAnim[i] = ImLerp(tabAnim[i], target, 0.14f);

        ImVec4 col = ImLerp(BASE_SURFACE, ACCENT, tabAnim[i]);

        ImVec4 hover  = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.18f);
        ImVec4 activeC = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 0.28f);

        ImGui::PushStyleColor(ImGuiCol_Button, col);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hover);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeC);

        if (ImGui::Button(tabs[i], ImVec2(-1, 38)))
            menu_idx = i;

        ImGui::PopStyleColor(3);

        ImGui::Spacing();
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

// ─────────────────────────────
// Config helper
// ─────────────────────────────
static std::vector<std::string> GetConfigFiles()
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
// Main Menu
// ─────────────────────────────
void Menu()
{
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, MenuAlpha);

    ImGui::SetNextWindowSize(ImVec2(800, 500));
    ImGui::Begin("Lunari " LUNARI_VERSION, nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse);

    MenuWindowPos = ImGui::GetWindowPos();

    RenderStarBackground(ImGui::GetWindowDrawList(),
        MenuWindowPos,
        ImGui::GetWindowSize(),
        1);

    ImGui::Spacing();

    // ───────── TAB: RECOIL ─────────
    if (menu_idx == 0)
    {
        ImGui::Text("Recoil Control");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Enabled", &RecoilToggle);

        ImGui::SliderFloat("Recoil X", &config.RecoilX, -100, 100);
        ImGui::SameLine(); if (ImGui::Button("Reset##X")) config.RecoilX = 0;

        ImGui::SliderFloat("Recoil Y", &config.RecoilY, -100, 100);
        ImGui::SameLine(); if (ImGui::Button("Reset##Y")) config.RecoilY = 0;

        ImGui::SliderFloat("Smoothing X", &config.SmoothingX, 0, 0.100);
        ImGui::SameLine(); if (ImGui::Button("Reset##SX")) config.SmoothingX = 0;

        ImGui::SliderFloat("Smoothing Y", &config.SmoothingY, 0, 100);
        ImGui::SameLine(); if (ImGui::Button("Reset##SY")) config.SmoothingY = 0;

        ImGui::SliderFloat("Humanize", &config.Humanize, 0, 100);
        ImGui::SameLine(); if (ImGui::Button("Reset##H")) config.Humanize = 0;
    }

    // ───────── TAB: CONFIGS ─────────
else if (menu_idx == 1)
{
    static std::vector<std::string> cfgs;
    static int selected = -1;

    // Refresh on every tab visit so list stays current
    auto Refresh = [&]()
    {
        cfgs = GetConfigFiles();
        if (selected >= (int)cfgs.size())
            selected = -1;
    };

    config.SetupConfigFolder();

    ImGui::InputText("Name##save", ConfigSaveName, IM_ARRAYSIZE(ConfigSaveName));

    if (ImGui::Button("Save") && ConfigSaveName[0] != '\0')
    {
        config.SaveConfig(ConfigSaveName);
        Refresh();
    }

    ImGui::SameLine();

    if (ImGui::Button("Load") && selected >= 0 && selected < (int)cfgs.size())
    {
        std::string name = cfgs[selected];
        // Strip .cfg extension before passing to LoadConfig
        if (auto pos = name.find_last_of('.'); pos != std::string::npos)
            name = name.substr(0, pos);
        config.LoadConfig(name);
    }

    ImGui::SameLine();

    if (ImGui::Button("Refresh"))
        Refresh();

    // Populate on first render of this tab
    if (cfgs.empty())
        Refresh();

    std::vector<const char*> items;
    items.reserve(cfgs.size());
    for (auto& c : cfgs)
        items.push_back(c.c_str());

    ImGui::Spacing();

    if (items.empty())
        ImGui::TextDisabled("No configs found in C:/Lunari/Recoil/Configs");
    else
        ImGui::ListBox("##cfglist", &selected, items.data(), (int)items.size(), 8);
}

    // ───────── TAB: SETTINGS ─────────
    else if (menu_idx == 2)
    {
        if (ImGui::Button("Exit"))
            window.running = false;
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

// ─────────────────────────────
// Preview
// ─────────────────────────────
void RecoilPreview()
{
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, MenuAlpha);

    ImGui::SetNextWindowSize(ImVec2(200, 500));
    ImGui::SetNextWindowPos(ImVec2(MenuWindowPos.x + 800, MenuWindowPos.y));

    ImGui::Begin("Preview", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoInputs);

    RenderStarBackground(ImGui::GetWindowDrawList(),
        ImGui::GetWindowPos(),
        ImGui::GetWindowSize(),
        2);

    ImVec2 center(
        ImGui::GetWindowPos().x + ImGui::GetWindowSize().x * 0.5f,
        ImGui::GetWindowPos().y + ImGui::GetWindowSize().y * 0.5f
    );

    recoil.DrawMousePreview(ImGui::GetWindowDrawList(),
        center,
        config.RecoilX, config.RecoilY,
        config.SmoothingX, config.SmoothingY,
        config.Humanize);

    ImGui::End();
    ImGui::PopStyleVar();
}