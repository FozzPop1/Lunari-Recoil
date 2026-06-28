#include "../../../inc/gui/menu.h"
#include "../../../inc/version.h"
#include "../../../resource/fonts/fontawesome6.h"
#include "../../../inc/macro/config.h"

void RecoilMenu() {
    if (menu_idx == 0)
    {
        ImGui::Text(" Recoil Control");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Enabled", &RecoilToggle);

        ImGui::SetNextItemWidth(-80.0f);
        ImGui::SliderFloat("##RecoilX", &config.RecoilX, -100.0f, 100.0f, "X: %.1f");
        ImGui::SameLine();
        if (ImGui::Button("Reset##X", ImVec2(70.0f, 0))) config.RecoilX = 0.0f;

        ImGui::SetNextItemWidth(-80.0f);
        ImGui::SliderFloat("##RecoilY", &config.RecoilY, -100.0f, 100.0f, "Y: %.1f");
        ImGui::SameLine();
        if (ImGui::Button("Reset##Y", ImVec2(70.0f, 0))) config.RecoilY = 0.0f;

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // ---- Smoothing ----
        ImGui::TextDisabled("Smoothing");
        ImGui::Spacing();

        ImGui::SetNextItemWidth(-80.0f);
        ImGui::SliderFloat("##SmoothX", &config.SmoothingX, 0.0f, 0.99f, "X: %.2f");
        ImGui::SameLine();
        if (ImGui::Button("Reset##SX", ImVec2(70.0f, 0))) config.SmoothingX = 0.0f;

        ImGui::SetNextItemWidth(-80.0f);
        ImGui::SliderFloat("##SmoothY", &config.SmoothingY, 0.0f, 0.99f, "Y: %.2f");
        ImGui::SameLine();
        if (ImGui::Button("Reset##SY", ImVec2(70.0f, 0))) config.SmoothingY = 0.0f;

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // ---- Humanize ----
        ImGui::TextDisabled("Humanize");
        ImGui::Spacing();

        ImGui::SetNextItemWidth(-80.0f);
        ImGui::SliderFloat("##Humanize", &config.Humanize, 0.0f, 100.0f, "%.1f");
        ImGui::SameLine();
        if (ImGui::Button("Reset##H", ImVec2(70.0f, 0))) config.Humanize = 0.0f;
    }
}