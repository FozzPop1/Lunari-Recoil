#pragma once

#include "../../ext/inc/Imgui/imgui.h"

class Recoil {
    private:

    public:

    void MoveMouseRel(float x, float y, float smoothingX, float smoothingY, float humanizeAmount);
    
    void DrawMousePreview(ImDrawList* drawList, ImVec2 origin,
                      float velX, float velY,
                      float smoothingX, float smoothingY,
                      float humanizeAmount, int steps = 60);
};

extern Recoil recoil;