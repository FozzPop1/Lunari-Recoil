#include "../../../inc/gui/menu.h"
#include "../../../inc/macro/recoil.h"
#include "../../../inc/macro/config.h"

void RecoilPreview() {
    ImGui::BeginChild("##preview", ImVec2(0, 0), false, ImGuiWindowFlags_NoInputs);

    ImGui::Text(" Preview");
    ImGui::Separator();

    ImVec2 childPos  = ImGui::GetWindowPos();
    ImVec2 childSize = ImGui::GetWindowSize();

    ImVec2 center(
        childPos.x + childSize.x * 0.5f,
        childPos.y + childSize.y * 0.5f
    );

    recoil.DrawMousePreview(
        ImGui::GetWindowDrawList(),
        center,
        config.RecoilX, config.RecoilY,
        config.SmoothingX, config.SmoothingY,
        config.Humanize, 60, MenuAlpha);

    ImGui::EndChild();
}