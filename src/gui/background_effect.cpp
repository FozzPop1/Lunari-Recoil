#include "../../inc/gui/background_effect.h"

#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

void RenderStarBackground(ImDrawList* draw_list, ImVec2 pos, ImVec2 size) {
    struct Star {
        float x, y, speed, radius;
        float alpha, alphaDir, alphaSpeed;
        float trail;
        float hue;        // slight color variation per star
        float twinklePhase;
        int   layer;      // 0=far 1=mid 2=close (parallax)
    };

    static std::vector<Star> stars;
    static bool  init = false;
    static float time = 0.f;

    time += 0.016f; // ~60fps delta, swap for real delta if you have it

    if (!init) {
        stars.resize(200);
        for (auto& s : stars) {
            s.layer        = rand() % 3;
            s.x            = (float)(rand() % (int)size.x);
            s.y            = (float)(rand() % (int)size.y);
            float layerSpd = 0.2f + s.layer * 0.6f;
            s.speed        = layerSpd + (rand() % 100) / 100.f * 0.8f;
            s.radius       = 0.3f + s.layer * 0.5f + (rand() % 100) / 100.f * 0.8f;
            s.alpha        = (rand() % 100) / 100.f;
            s.alphaSpeed   = 0.003f + (rand() % 100) / 100.f * 0.008f;
            s.alphaDir     = rand() % 2 ? 1.f : -1.f;
            s.trail        = s.speed * (3.f + s.layer * 2.5f);
            s.hue          = (rand() % 100) / 100.f; // 0=blue-white 1=purple-white
            s.twinklePhase = (rand() % 628) / 100.f; // random phase offset
        }
        init = true;
    }

    // soft nebula glow blobs in background for depth
    auto Nebula = [&](float nx, float ny, float nr, float r, float g, float b, float a) {
        const int steps = 6;
        for (int i = steps; i >= 1; i--) {
            float t    = (float)i / steps;
            float rad  = nr * t;
            float fade = a * (1.f - t) * 0.18f;
            ImU32 col  = ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, fade));
            draw_list->AddCircleFilled(ImVec2(pos.x + nx, pos.y + ny), rad, col, 32);
        }
    };

    // slow drifting nebula clouds — positions oscillate gently
    Nebula(size.x * 0.2f + sinf(time * 0.03f) * 20.f, size.y * 0.3f, size.x * 0.28f, 0.4f, 0.3f, 0.9f, 1.f);
    Nebula(size.x * 0.75f + cosf(time * 0.02f) * 15.f, size.y * 0.6f, size.x * 0.22f, 0.2f, 0.4f, 1.0f, 1.f);
    Nebula(size.x * 0.5f,  size.y * 0.15f + sinf(time * 0.025f) * 10.f, size.x * 0.18f, 0.6f, 0.2f, 0.8f, 1.f);

    for (auto& s : stars) {
        s.y += s.speed;

        // twinkle via sine wave for smooth organic pulse
        float twinkle = 0.5f + 0.5f * sinf(time * (1.5f + s.alphaSpeed * 80.f) + s.twinklePhase);
        float layerAlpha = 0.3f + s.layer * 0.25f; // far stars dimmer
        float finalAlpha = twinkle * layerAlpha;

        if (s.y > size.y + s.trail) {
            s.y            = -s.trail;
            s.x            = (float)(rand() % (int)size.x);
            s.twinklePhase = (rand() % 628) / 100.f;
        }

        // color: blend between icy blue-white and soft lavender based on hue
        float r = 0.75f + s.hue * 0.2f;
        float g = 0.82f + s.hue * 0.05f;
        float b = 1.0f;

        ImVec2 starPos  = ImVec2(pos.x + s.x, pos.y + s.y);
        ImVec2 trailTop = ImVec2(starPos.x, starPos.y - s.trail);

        // multi-segment trail that fades gracefully
        const int segments = 8;
        for (int i = 0; i < segments; i++) {
            float t0 = (float)i       / segments;
            float t1 = (float)(i + 1) / segments;
            ImVec2 p0 = ImVec2(starPos.x, trailTop.y + s.trail * t0);
            ImVec2 p1 = ImVec2(starPos.x, trailTop.y + s.trail * t1);
            float  a0 = finalAlpha * t0 * 0.6f;
            float  a1 = finalAlpha * t1 * 0.6f;
            ImU32 c0  = ImGui::ColorConvertFloat4ToU32(ImVec4(r * 0.6f, g * 0.7f, 1.f, a0));
            ImU32 c1  = ImGui::ColorConvertFloat4ToU32(ImVec4(r,        g,        1.f, a1));
            draw_list->AddLine(p0, p1, c0, s.radius * 0.5f);
            (void)c1;
        }

        // star core with a soft bloom — two circles, inner bright outer soft
        float bloomR = s.radius * 2.2f;
        ImU32 colBloom = ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, finalAlpha * 0.2f));
        ImU32 colCore  = ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, finalAlpha));
        draw_list->AddCircleFilled(starPos, bloomR,   colBloom, 12);
        draw_list->AddCircleFilled(starPos, s.radius, colCore,  8);
    }
}