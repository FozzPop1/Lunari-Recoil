#pragma once

#include "../../ext/inc/Imgui/imgui.h"

#include <vector>
#include <string>

// UI functions
void Menu();

void RecoilMenu();
void ConfigMenu();
void SettingsMenu();
void SidebarMenu();
void RecoilPreview();

// extra functions

std::vector<std::string> GetConfigFiles();

// -------------------------
// Global UI state
// -------------------------
extern bool ShowMenu;

extern ImVec2 MenuWindowPos;

extern std::vector<std::string> fileList;

extern bool RecoilToggle;

extern int menu_idx;
extern int selectedconfig;

extern char ConfigSaveName[256];
extern char ConfigLoadName[256];

extern float MenuAlpha;
extern ImVec2 SideBarPos;

extern ImFont* FontRegular;
extern ImFont* FontSemiBold;
extern ImFont* FontAwesome;

extern const ImVec4 ACCENT;
extern const ImVec4 BASE_SURFACE;

extern const char* tabs[];