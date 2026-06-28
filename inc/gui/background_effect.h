#pragma once

#include "../../ext/inc/Imgui/imgui.h"

#ifndef IM_PI
    #define IM_PI 3.14159265358979323846f
#endif

#include <windows.h>

void RenderStarBackground(ImDrawList* draw_list, ImVec2 pos, ImVec2 size, int windowId);