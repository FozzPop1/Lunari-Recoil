#include "../../inc/gui/background_effect.h"

#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <random>
#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

struct BGStar {
    float x, y, speed, radius;
    float alphaSpeed, trail, hue, twinklePhase;
    int layer;
};

struct BGWindow {
    std::vector<BGStar> stars;
    std::mt19937 rng;
    bool init     = false;
    int  lastMove = -1;
};

static BGWindow bgWindows[3];
static float    bgTime      = 0.f;
static int      bgLastFrame = -1;

static void BGInit(BGWindow& w, float width, float height, unsigned int seed)
{
    w.rng.seed(seed);

    std::uniform_real_distribution<float> distW(0.f, width);
    std::uniform_real_distribution<float> distH(0.f, height);
    std::uniform_real_distribution<float> dist01(0.f, 1.f);
    std::uniform_int_distribution<int>    distLayer(0, 2);

    w.stars.resize(180);

    for (auto& s : w.stars) {
        s.layer        = distLayer(w.rng);
        s.x            = distW(w.rng);
        s.y            = distH(w.rng);
        s.speed        = 0.18f + s.layer * 0.45f + dist01(w.rng) * 0.4f;
        s.radius       = 0.25f + s.layer * 0.35f + dist01(w.rng) * 0.5f;
        s.alphaSpeed   = 0.0025f + dist01(w.rng) * 0.006f;
        s.trail        = s.speed * (2.5f + s.layer * 2.0f);
        s.hue          = dist01(w.rng);
        s.twinklePhase = dist01(w.rng) * 6.28f;
    }

    w.init = true;
}

void RenderStarBackground(ImDrawList* dl, ImVec2 pos, ImVec2 size, int windowId, float menuAlpha)
{
    if (menuAlpha <= 0.004f) return; // nothing to draw

    int frame = ImGui::GetFrameCount();
    if (frame != bgLastFrame) {
        bgTime     += ImGui::GetIO().DeltaTime; // framerate-independent
        bgLastFrame = frame;
    }

    int id        = windowId % 3;
    BGWindow& w   = bgWindows[id];

    if (!w.init)
        BGInit(w, size.x, size.y, (unsigned)(id * 1000003u + 999983u));

    float lt = bgTime + id * 137.f;

    std::uniform_real_distribution<float> distW(0.f, size.x);
    std::uniform_real_distribution<float> dist01(0.f, 1.f);

    // helper — multiplies any alpha value by menuAlpha
    auto A = [&](float a) { return a * menuAlpha; };

    dl->PushClipRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), true);

    // background rect
    dl->AddRectFilled(
        pos,
        ImVec2(pos.x + size.x, pos.y + size.y),
        IM_COL32(3, 6, 12, (int)(235 * menuAlpha))
    );

    // nebula — 'na' avoids shadowing the outer menuAlpha
    auto Nebula = [&](float nx, float ny, float nr, float r, float g, float b, float na)
    {
        for (int i = 5; i >= 1; i--) {
            float t        = (float)i / 5.f;
            float nebulaA  = A(na * (1.f - t) * 0.10f);

            dl->AddCircleFilled(
                ImVec2(pos.x + nx, pos.y + ny),
                nr * t,
                ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, nebulaA)),
                24
            );
        }
    };

    Nebula(size.x * 0.22f + sinf(lt * 0.02f)  * 18.f, size.y * 0.32f,
           size.x * 0.26f, 0.20f, 0.35f, 0.65f, 1.f);

    Nebula(size.x * 0.72f + cosf(lt * 0.018f) * 14.f, size.y * 0.62f,
           size.x * 0.22f, 0.15f, 0.30f, 0.60f, 1.f);

    Nebula(size.x * 0.50f, size.y * 0.18f + sinf(lt * 0.022f) * 10.f,
           size.x * 0.18f, 0.25f, 0.25f, 0.55f, 1.f);

    bool doMove = (w.lastMove != frame);

    for (auto& s : w.stars)
    {
        if (doMove)
            s.y += s.speed;

        if (s.y > size.y + s.trail) {
            s.y            = -s.trail;
            s.x            = distW(w.rng);
            s.twinklePhase = dist01(w.rng) * 6.28f;
        }

        float twinkle = 0.5f + 0.5f * sinf(lt * (1.2f + s.alphaSpeed * 70.f) + s.twinklePhase);
        float starA   = twinkle * (0.25f + s.layer * 0.22f);

        float r = 0.85f + s.hue * 0.10f;
        float g = 0.90f + s.hue * 0.08f;
        float b = 1.00f;

        ImVec2 starPos(pos.x + s.x, pos.y + s.y);
        ImVec2 trailTop(starPos.x, starPos.y - s.trail);

        // trail
        for (int i = 0; i < 6; i++) {
            float t0 = (float)i       / 6.f;
            float t1 = (float)(i + 1) / 6.f;

            ImVec2 p0(starPos.x, trailTop.y + s.trail * t0);
            ImVec2 p1(starPos.x, trailTop.y + s.trail * t1);

            dl->AddLine(
                p0, p1,
                ImGui::ColorConvertFloat4ToU32(ImVec4(r * 0.7f, g * 0.8f, b, A(starA * t1 * 0.4f))),
                s.radius * 0.35f
            );
        }

        // glow
        dl->AddCircleFilled(
            starPos,
            s.radius * 1.8f,
            ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, A(starA * 0.15f))),
            10
        );

        // core
        dl->AddCircleFilled(
            starPos,
            s.radius,
            ImGui::ColorConvertFloat4ToU32(ImVec4(1.f, 1.f, 1.f, A(starA))),
            8
        );
    }

    if (doMove)
        w.lastMove = frame;

    dl->PopClipRect();
}