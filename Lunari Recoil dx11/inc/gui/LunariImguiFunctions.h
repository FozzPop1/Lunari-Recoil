#pragma once

#include "../../ext/inc/Imgui/imgui.h"
#include "../../ext/inc/Imgui/imgui_internal.h"
#include <vector>
#include <cmath>

//------------------------------------------------------------
// Frame-rate independent smoothing
//------------------------------------------------------------

static inline float SmoothLerp(float current, float target, float speed)
{
    const float dt = ImGui::GetIO().DeltaTime;

    // speed = 12 feels very smooth
    const float alpha = 1.0f - expf(-speed * dt);

    return current + (target - current) * alpha;
}

//------------------------------------------------------------
// Animated Slider
//------------------------------------------------------------

static void DrawLagSlider(
    const char* id,
    float* value,
    float* lerped,
    float min,
    float max,
    const char* fmt,
    const char* resetId,
    float resetValue,
    float smoothSpeed = 12.0f)
{
    ImGui::PushStyleColor(ImGuiCol_FrameBg,          ImVec4(0.12f,0.12f,0.18f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,   ImVec4(0.18f,0.18f,0.28f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive,    ImVec4(0.22f,0.22f,0.34f,1.0f));

    ImGui::PushStyleColor(ImGuiCol_SliderGrab,       ImVec4(0.42f,0.63f,1.00f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.58f,0.80f,1.00f,1.0f));

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,6.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding,12.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(4,6));

    ImGui::SetNextItemWidth(-80.0f);

    float display = *lerped;

    ImGui::SliderFloat(id, &display, min, max, fmt);

    bool active = ImGui::IsItemActive();

    if (active)
    {
        *value  = display;
        *lerped = display;
    }
    else
    {
        *lerped = SmoothLerp(*lerped, *value, smoothSpeed);

        // Prevent tiny floating point jitter.
        if (fabsf(*lerped - *value) < 0.0001f)
            *lerped = *value;
    }

    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(5);

    //--------------------------------------------------------

    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.20f,0.20f,0.28f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.28f,0.28f,0.42f,1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.40f,0.60f,1.00f,1.0f));

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding,6.0f);

    if (ImGui::Button(resetId, ImVec2(70,0)))
    {
        *value  = resetValue;
        *lerped = resetValue;
        ImGui::ClearActiveID();
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
}