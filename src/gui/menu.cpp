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

// -------------------------
// Globals
// -------------------------
ImVec2 MenuWindowPos;

bool ShowMenu = true;
bool RecoilToggle;

int menu_idx = 0;

char ConfigSaveName[256] = "user";
char ConfigLoadName[256] = { 0 };

float MenuAlpha = 0.0f;
static float tabAnim[3] = { 0.0f, 0.0f, 0.0f };

ImVec2 SideBarPos;

// -------------------------
// Tabs
// -------------------------
static const char* tabs[] = {
    "Recoil",
    "Configs",
    "Settings"
};

// -------------------------
// Sidebar
// -------------------------
void Sidebar()
{
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, MenuAlpha);

    ImGui::SetNextWindowSize(ImVec2(200, 500));
    ImGui::SetNextWindowPos(ImVec2(MenuWindowPos.x - 220, MenuWindowPos.y));

    ImGui::Begin(
        "Lunari Recoil",
        nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar
    );

    SideBarPos = ImGui::GetWindowPos();

    RenderStarBackground(ImGui::GetWindowDrawList(),
        ImGui::GetWindowPos(),
        ImGui::GetWindowSize());

    ImGui::Spacing();

    for (int i = 0; i < 3; i++)
    {
        bool active = (menu_idx == i);

        // ── Smooth animation (fade 0 → 1) ───────────────
        float target = active ? 1.0f : 0.0f;
        tabAnim[i] = ImLerp(tabAnim[i], target, 0.12f);

        // ── Colors based on animation ────────────────────
        ImVec4 base      = ImVec4(0.10f, 0.10f, 0.14f, 1.0f);
        ImVec4 accent    = ImVec4(0.45f, 0.38f, 0.90f, 1.0f);

        ImVec4 col       = ImLerp(base, accent, tabAnim[i]);
        ImVec4 hoverCol  = ImVec4(accent.x, accent.y, accent.z, 0.35f * tabAnim[i]);
        ImVec4 activeCol = ImVec4(accent.x, accent.y, accent.z, 0.50f * tabAnim[i]);

        ImGui::PushStyleColor(ImGuiCol_Button, col);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverCol);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeCol);

        if (ImGui::Button(tabs[i], ImVec2(-1, 40)))
            menu_idx = i;

        ImGui::PopStyleColor(3);

        ImGui::Spacing();
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

// -------------------------
// Config helper
// -------------------------
static std::vector<std::string> GetConfigFiles()
{
    std::vector<std::string> files;

    const std::string path = "C:/Lunari/Recoil/Configs";

    if (!std::filesystem::exists(path))
        return files;

    for (const auto& p : std::filesystem::directory_iterator(path))
    {
        if (p.path().extension() == ".cfg")
            files.push_back(p.path().filename().string());
    }

    return files;
}

// -------------------------
// Main Menu
// -------------------------
void Menu()
{
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, MenuAlpha);

    ImGui::SetNextWindowSize(ImVec2(800, 500));
    ImGui::Begin(
        "Version " LUNARI_VERSION,
        nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse
    );

    MenuWindowPos = ImGui::GetWindowPos();

    RenderStarBackground(ImGui::GetWindowDrawList(),
        MenuWindowPos,
        ImGui::GetWindowSize());

    ImGui::Spacing();

    // -------------------------
    // TAB 0: Recoil
    // -------------------------
    if (menu_idx == 0)
    {
        ImGui::Text("Recoil Control");
        ImGui::Separator();
        ImGui::Spacing();

        // Recoil Checkbox

        ImGui::Checkbox("Recoil", &RecoilToggle);

        ImGui::Spacing();

        // Recoil Sliders

        ImGui::SliderFloat("Recoil X", &config.RecoilX, -100.0f, 100.0f);
        ImGui::SameLine();
        if (ImGui::Button("Rest##X")) {
            config.RecoilX = 0;
        }

        ImGui::SliderFloat("Recoil Y", &config.RecoilY, -100.0f, 100.0f);
            ImGui::SameLine();
        if (ImGui::Button("Rest##Y")) {
            config.RecoilY = 0;
        }
    }

    // -------------------------
    // TAB 1: Configs
    // -------------------------
    else if (menu_idx == 1)
    {
        static std::vector<std::string> configFiles;
        static int selectedIdx = -1;

        static auto RefreshConfigs = [&]()
        {
            configFiles = GetConfigFiles();
        };

        if (configFiles.empty())
            RefreshConfigs();

        ImGui::InputText("Config Name", ConfigSaveName, IM_ARRAYSIZE(ConfigSaveName));

        ImGui::Spacing();
        ImGui::Spacing();

        if (ImGui::Button("Save"))
        {
            config.SaveConfig(ConfigSaveName);
            RefreshConfigs();
        }

        ImGui::SameLine();

        if (ImGui::Button("Load") && selectedIdx >= 0 && selectedIdx < (int)configFiles.size())
        {
            config.LoadConfig(configFiles[selectedIdx]);
        }

        ImGui::SameLine();

        if (ImGui::Button("Refresh"))
            RefreshConfigs();

        ImGui::Spacing();
        ImGui::Spacing();

        std::vector<const char*> items;
        items.reserve(configFiles.size());

        for (auto& f : configFiles)
            items.push_back(f.c_str());

        ImGui::ListBox("##configs", &selectedIdx, items.data(), (int)items.size(), 6);

        if (selectedIdx >= 0 && selectedIdx < (int)configFiles.size())
        {
            strncpy_s(
                ConfigLoadName,
                configFiles[selectedIdx].c_str(),
                sizeof(ConfigLoadName) - 1
            );
        }
    }

    // -------------------------
    // TAB 2: Settings
    // -------------------------
    else if (menu_idx == 2)
    {
        if (ImGui::Button("Exit"))
        {
            window.running = false;
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}