#include "../../inc/gui/menu.h"

#include "../../inc/macro/config.h"
#include "../../inc/macro/recoil.h"

#include "../../ext/inc/Imgui/imgui.h"
#include "../../inc/gui/background_effect.h"

#include "../../inc/gui/window.h"

#include <filesystem>
#include <vector>

ImVec2 MenuWindowPos;

std::vector<std::string> fileList;

bool RecoilToggle;

const char* tabs[] = { "Recoil", "Configs", "Settings" };

int menu_idx;
int selectedconfig = -1;

char ConfigSaveName[256] = "user.cfg";
char ConfigLoadName[256];

/*
    Side Bar Logic
*/

void Sidebar() {
    ImGui::SetNextWindowSize(ImVec2(200, 500));
    ImGui::SetNextWindowPos(ImVec2(MenuWindowPos.x - 220, MenuWindowPos.y));
    ImGui::Begin("Lunari Recoil", 0, 
    ImGuiWindowFlags_NoResize | 
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoMove);

    ImVec2 win_pos  = ImGui::GetWindowPos();
    ImVec2 win_size = ImGui::GetWindowSize();
    RenderStarBackground(ImGui::GetWindowDrawList(), win_pos, win_size);

    for (int i = 0; i < 3; i++) {
        bool active = (menu_idx == i);
        if (active) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 0.8f));
        if (active) ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.5f, 0.8f));
        if (active) ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 0.8f));
        if (ImGui::Button(tabs[i], ImVec2(175, 40))) menu_idx = i;
        if (active) ImGui::PopStyleColor(3);
    }
    
    
    ImGui::End();
}

/*
    Menu Logic
*/

void Menu() {
    ImGui::SetNextWindowSize(ImVec2(800, 500));
    ImGui::Begin("Version 1.0", 0,
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoCollapse);
    
    MenuWindowPos = ImGui::GetWindowPos();

    ImVec2 win_size = ImGui::GetWindowSize();
    RenderStarBackground(ImGui::GetWindowDrawList(), MenuWindowPos, win_size);

    if (menu_idx == 0) {
        ImGui::Checkbox("Recoil", &RecoilToggle);
        
        ImGui::Spacing();
        
        ImGui::SliderFloat("Recoil X", &config.RecoilX, -100, 100);
        ImGui::SliderFloat("Recoil Y", &config.RecoilY, -100, 100);
    }

    if (menu_idx == 1) {
        static std::vector<std::string> configFiles;
        static int selectedIdx = -1;
        // Scan once + on demand
        auto RefreshConfigs = [&]() {
        configFiles.clear();
        
        for (auto& p : std::filesystem::directory_iterator("configs"))
            if (p.path().extension() == ".cfg")
            configFiles.push_back(p.path().filename().string());
        };

        if (configFiles.empty()) RefreshConfigs();

        ImGui::InputText("Config Name", ConfigSaveName, IM_ARRAYSIZE(ConfigSaveName));

        for (int i = 0; i < 3; i++) {
            ImGui::Spacing();
        }

        if (ImGui::Button("Save"))  { config.SaveConfig(ConfigSaveName); RefreshConfigs(); }
        ImGui::SameLine();
        if (ImGui::Button("Load") && selectedIdx >= 0) config.LoadConfig(configFiles[selectedIdx]);
        ImGui::SameLine();
        if (ImGui::Button("Refresh")) RefreshConfigs();

        for (int i = 0; i < 3; i++) {
            ImGui::Spacing();
        }

        std::vector<const char*> items;
        for (auto& f : configFiles) items.push_back(f.c_str());
        ImGui::ListBox("##configs", &selectedIdx, items.data(), (int)items.size(), 6);

        if (selectedIdx >= 0)
            strncpy(ConfigLoadName, configFiles[selectedIdx].c_str(), 256);
    }

    if (menu_idx == 2) {
        if (ImGui::Button("Exit")) {
            window.running = false;
        }
    }

    ImGui::End();
}