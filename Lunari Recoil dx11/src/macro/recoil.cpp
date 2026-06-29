#define NOMINMAX

#include <windows.h>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

#include "../../inc/macro/recoil.h"

// -------------------------------------------------
// Internal simulation state
// -------------------------------------------------
struct MotionState
{
    float accumX = 0.0f;
    float accumY = 0.0f;

    float smoothX = 0.0f;
    float smoothY = 0.0f;

    float driftX = 0.0f;
    float driftY = 0.0f;

    std::mt19937 rng{ std::random_device{}() };
    std::normal_distribution<float> gauss{ 0.0f, 1.0f };

    inline float noise() { return gauss(rng); }
};

static MotionState state;

void Recoil::ApplyDelta(int dx, int dy)
{
    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    SendInput(1, &input, sizeof(INPUT));
}

void Recoil::MoveMouseRel(
    float x,
    float y,
    float smoothingX,
    float smoothingY,
    float humanize)
{
    smoothingX = std::clamp(smoothingX, 0.0f, 0.99f);
    smoothingY = std::clamp(smoothingY, 0.0f, 0.99f);

    const float lerpX = 1.0f - smoothingX;
    const float lerpY = 1.0f - smoothingY;

    state.driftX += state.noise() * humanize * 0.08f;
    state.driftY += state.noise() * humanize * 0.08f;

    state.driftX *= 0.92f;
    state.driftY *= 0.92f;

    const float cap = humanize * 0.6f;
    state.driftX = std::clamp(state.driftX, -cap, cap);
    state.driftY = std::clamp(state.driftY, -cap, cap);

    float jitterX = state.noise() * humanize * 0.12f;
    float jitterY = state.noise() * humanize * 0.12f;

    float targetX = x + state.driftX + jitterX;
    float targetY = y + state.driftY + jitterY;

    state.smoothX += lerpX * (targetX - state.smoothX);
    state.smoothY += lerpY * (targetY - state.smoothY);

    state.accumX += state.smoothX;
    state.accumY += state.smoothY;

    int dx = (int)state.accumX;
    int dy = (int)state.accumY;

    state.accumX -= dx;
    state.accumY -= dy;

    Recoil::ApplyDelta(dx, dy);
}

void Recoil::DrawMousePreview(ImDrawList* drawList, ImVec2 origin, float velX, float velY, float smoothingX, float smoothingY, float humanizeAmount, int steps, float menuAlpha)
{
    if (steps <= 0) steps = 1;

    const float previewRadius = 80.0f;

    const float lerpX = 1.0f - std::clamp(smoothingX, 0.0f, 0.99f);
    const float lerpY = 1.0f - std::clamp(smoothingY, 0.0f, 0.99f);

    // Separate seeds per axis so X/Y drift independently and don't cancel
    std::mt19937 rngX(1337), rngY(31337);
    std::normal_distribution<float> gauss(0.0f, 1.0f);

    float accumX = 0.0f, accumY = 0.0f;
    float smoothVelX = 0.0f, smoothVelY = 0.0f;
    float driftX = 0.0f, driftY = 0.0f;

    // Accumulate positions relative to (0,0) so raw[0] is always the origin
    std::vector<ImVec2> raw;
    raw.reserve(steps + 1);
    raw.push_back({ 0.0f, 0.0f });

    float curX = 0.0f, curY = 0.0f;

    for (int i = 0; i < steps; i++)
    {
        driftX += gauss(rngX) * humanizeAmount * 0.08f;
        driftY += gauss(rngY) * humanizeAmount * 0.08f;
        driftX *= 0.92f;
        driftY *= 0.92f;
        const float cap = humanizeAmount * 0.6f;
        driftX = std::clamp(driftX, -cap, cap);
        driftY = std::clamp(driftY, -cap, cap);

        float jitterX = gauss(rngX) * humanizeAmount * 0.12f;
        float jitterY = gauss(rngY) * humanizeAmount * 0.12f;

        float targetX = velX + driftX + jitterX;
        float targetY = velY + driftY + jitterY;

        smoothVelX += lerpX * (targetX - smoothVelX);
        smoothVelY += lerpY * (targetY - smoothVelY);

        accumX += smoothVelX;
        accumY += smoothVelY;

        int dx = (int)accumX;
        int dy = (int)accumY;
        accumX -= (float)dx;
        accumY -= (float)dy;

        curX += (float)dx;
        curY += (float)dy;

        raw.push_back({ curX, curY });
    }

    // Compute bounding box to derive scale
    float minX = raw[0].x, maxX = raw[0].x;
    float minY = raw[0].y, maxY = raw[0].y;
    for (auto& p : raw) {
        minX = std::min(minX, p.x); maxX = std::max(maxX, p.x);
        minY = std::min(minY, p.y); maxY = std::max(maxY, p.y);
    }

    const float rangeX = maxX - minX;
    const float rangeY = maxY - minY;
    const bool noMovement = (rangeX < 1.0f && rangeY < 1.0f);

    // Translate to screen space: raw[0] always maps to origin (center dot)
    std::vector<ImVec2> pts;
    if (!noMovement)
    {
        const float scale = (previewRadius * 0.9f) / std::max({ rangeX, rangeY, 1.0f });
        pts.reserve(raw.size());
        for (auto& p : raw)
        {
            pts.push_back({
                origin.x + p.x * scale,
                origin.y + p.y * scale
            });
        }
    }

    auto A  = [&](int a)   { return (int)(a * menuAlpha); };
    auto AF = [&](float a) { return a * menuAlpha; };

    // Background circle
    drawList->AddCircleFilled(origin, previewRadius + 10.0f, IM_COL32(15, 15, 20, A(180)));
    drawList->AddCircle(origin, previewRadius + 10.0f, IM_COL32(60, 60, 80, A(200)), 64, 1.5f);

    // Crosshair
    constexpr float ch = 8.0f;
    drawList->AddLine(ImVec2(origin.x - ch, origin.y), ImVec2(origin.x + ch, origin.y), IM_COL32(80, 80, 100, A(150)), 1.0f);
    drawList->AddLine(ImVec2(origin.x, origin.y - ch), ImVec2(origin.x, origin.y + ch), IM_COL32(80, 80, 100, A(150)), 1.0f);

    if (!noMovement && pts.size() > 1)
    {
        // Glow pass
        for (int i = 1; i < (int)pts.size(); i++)
        {
            float t = (float)i / (float)steps;
            ImU32 glow = ImGui::ColorConvertFloat4ToU32(ImVec4(0.2f, 0.6f + t * 0.4f, 1.0f, AF(0.08f)));
            drawList->AddLine(pts[i - 1], pts[i], glow, 6.0f);
        }

        // Main line
        for (int i = 1; i < (int)pts.size(); i++)
        {
            float t = (float)i / (float)steps;
            float alpha = AF(1.0f - t * 0.4f);
            ImU32 color = ImGui::ColorConvertFloat4ToU32(
                ImVec4(t, 1.0f - t * 0.5f, 1.0f, alpha)
            );
            float thickness = 2.5f - t * 1.0f;
            drawList->AddLine(pts[i - 1], pts[i], color, thickness);
        }

        // End dot
        ImVec2 endPt = pts.back();
        drawList->AddCircleFilled(endPt, 5.0f, IM_COL32(255, 80, 120, A(60)));
        drawList->AddCircleFilled(endPt, 3.0f, IM_COL32(255, 80, 120, A(255)));
    }

    // Start dot — always drawn on top at exact origin
    drawList->AddCircleFilled(origin, 7.0f, IM_COL32(100, 220, 255, A(40)));
    drawList->AddCircleFilled(origin, 4.0f, IM_COL32(100, 220, 255, A(255)));
}

Recoil recoil;