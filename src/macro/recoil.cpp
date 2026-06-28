#define NOMINMAX

#include "../../inc/macro/recoil.h"

#include <windows.h>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime> 
/*
    Function to move the mouse
*/

void Recoil::MoveMouseRel(float x, float y, float smoothingX, float smoothingY, float humanizeAmount)
{
    static float accumX = 0.0f;
    static float accumY = 0.0f;
    static float smoothVelX = 0.0f;
    static float smoothVelY = 0.0f;

    auto randNoise = [](float scale) -> float {
        return scale * (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f);
    };

    float noisyX = x + randNoise(humanizeAmount);
    float noisyY = y + randNoise(humanizeAmount);

    float lerpX = 1.0f - std::clamp(smoothingX, 0.0f, 0.99f);
    float lerpY = 1.0f - std::clamp(smoothingY, 0.0f, 0.99f);

    smoothVelX = smoothVelX + lerpX * (noisyX - smoothVelX);
    smoothVelY = smoothVelY + lerpY * (noisyY - smoothVelY);

    accumX += smoothVelX;
    accumY += smoothVelY;

    LONG dx = static_cast<LONG>(accumX);
    LONG dy = static_cast<LONG>(accumY);

    accumX -= static_cast<float>(dx);
    accumY -= static_cast<float>(dy);

    if (dx | dy)
        mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(dx), static_cast<DWORD>(dy), 0, 0);
}

void Recoil::DrawMousePreview(ImDrawList* drawList, ImVec2 origin, float velX, float velY, float smoothingX, float smoothingY, float humanizeAmount, int steps) {
    float accumX = 0.0f, accumY = 0.0f;
    float smoothVelX = velX, smoothVelY = velY;
    float curX = origin.x, curY = origin.y;

    float lerpX = 1.0f - std::clamp(smoothingX, 0.0f, 0.99f);
    float lerpY = 1.0f - std::clamp(smoothingY, 0.0f, 0.99f);

    srand(42);

    std::vector<ImVec2> points;
    points.push_back(origin);

    for (int i = 0; i < steps; i++)
    {
        float noisyX = velX + humanizeAmount * ((float)rand() / RAND_MAX * 2.0f - 1.0f);
        float noisyY = velY + humanizeAmount * ((float)rand() / RAND_MAX * 2.0f - 1.0f);

        smoothVelX = smoothVelX + lerpX * (noisyX - smoothVelX);
        smoothVelY = smoothVelY + lerpY * (noisyY - smoothVelY);

        accumX += smoothVelX;
        accumY += smoothVelY;

        LONG dx = static_cast<LONG>(accumX);
        LONG dy = static_cast<LONG>(accumY);

        accumX -= static_cast<float>(dx);
        accumY -= static_cast<float>(dy);

        curX += static_cast<float>(dx);
        curY += static_cast<float>(dy);

        points.push_back(ImVec2(curX, curY));
    }

    srand((unsigned)time(nullptr));

    // Bounding box + scale to fit preview
    float minX = points[0].x, maxX = points[0].x;
    float minY = points[0].y, maxY = points[0].y;
    for (auto& p : points) {
        minX = std::min(minX, p.x); maxX = std::max(maxX, p.x);
        minY = std::min(minY, p.y); maxY = std::max(maxY, p.y);
    }

    float rangeX = maxX - minX;
    float rangeY = maxY - minY;
    bool noMovement = (rangeX < 1.0f && rangeY < 1.0f);

    std::vector<ImVec2> scaled;
    if (!noMovement)
    {
        float previewSize = 140.0f;
        float scale = previewSize / std::max({ rangeX, rangeY, 1.0f });

        for (auto& p : points)
        {
            float sx = origin.x + (p.x - points[0].x) * scale;
            float sy = origin.y + (p.y - points[0].y) * scale;
            scaled.push_back(ImVec2(sx, sy));
        }
    }

    // Background circle
    drawList->AddCircleFilled(origin, 90.0f, IM_COL32(15, 15, 20, 180));
    drawList->AddCircle(origin, 90.0f, IM_COL32(60, 60, 80, 200), 64, 1.5f);

    // Crosshair
    float ch = 8.0f;
    drawList->AddLine(ImVec2(origin.x - ch, origin.y), ImVec2(origin.x + ch, origin.y), IM_COL32(80, 80, 100, 150), 1.0f);
    drawList->AddLine(ImVec2(origin.x, origin.y - ch), ImVec2(origin.x, origin.y + ch), IM_COL32(80, 80, 100, 150), 1.0f);

    if (!noMovement && scaled.size() > 1)
    {
        // Glow pass (wide, transparent)
        for (int i = 1; i < (int)scaled.size(); i++)
        {
            float t = (float)i / steps;
            ImU32 glow = ImGui::ColorConvertFloat4ToU32(ImVec4(0.2f, 0.6f + t * 0.4f, 1.0f, 0.08f));
            drawList->AddLine(scaled[i - 1], scaled[i], glow, 6.0f);
        }

        // Main line with color fade (cyan -> magenta)
        for (int i = 1; i < (int)scaled.size(); i++)
        {
            float t = (float)i / steps;
            float alpha = 1.0f - t * 0.4f; // fade out toward end
            ImU32 color = ImGui::ColorConvertFloat4ToU32(
                ImVec4(t, 1.0f - t * 0.5f, 1.0f, alpha)
            );
            float thickness = 2.5f - t * 1.0f; // thin out toward end
            drawList->AddLine(scaled[i - 1], scaled[i], color, thickness);
        }

        // End dot with glow
        ImVec2 endPt = scaled.back();
        drawList->AddCircleFilled(endPt, 5.0f, IM_COL32(255, 80, 120, 60));
        drawList->AddCircleFilled(endPt, 3.0f, IM_COL32(255, 80, 120, 255));
    }

    // Start dot with glow
    drawList->AddCircleFilled(origin, 7.0f, IM_COL32(100, 220, 255, 40));
    drawList->AddCircleFilled(origin, 4.0f, IM_COL32(100, 220, 255, 255));
}

Recoil recoil;