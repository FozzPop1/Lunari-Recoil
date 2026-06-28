#pragma once

#include "../../ext/inc/Imgui/imgui.h"

#include <vector>
#include <string>

// UI functions
void Sidebar();
void Menu();
void RecoilPreview();

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