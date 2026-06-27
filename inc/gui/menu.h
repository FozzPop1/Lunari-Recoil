#pragma once

#include "../../ext/inc/Imgui/imgui.h"

#include <vector>
#include <string>

void Sidebar();
void Menu();

extern bool ShowMenu;

extern ImVec2 MenuWindowPos;

extern std::vector<std::string> fileList;

extern bool RecoilToggle;

extern const char* tabs[];

extern int menu_idx;
extern int selectedconfig;

extern char ConfigSaveName[256];
extern char ConfigLoadName[256];