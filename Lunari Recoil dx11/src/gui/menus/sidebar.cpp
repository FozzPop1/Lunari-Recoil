#include "../../../inc/gui/menu.h"
#include "../../../inc/version.h"
#include "../../../resource/fonts/fontawesome6.h"
#include "../../../ext/inc/Imgui/imgui_internal.h"

const ImVec4 ACCENT       = ImVec4(0.25f, 0.55f, 1.00f, 1.0f);
const ImVec4 BASE_SURFACE = ImVec4(0.09f, 0.10f, 0.13f, 1.0f);

const char* tabs[] = {
    ICON_FA_COMPUTER_MOUSE" Recoil ",
    ICON_FA_GEAR" Configs",
    ICON_FA_SLIDERS" Settings"
};

float tabAnim[3] = { 0.0f, 0.0f, 0.0f };

void SidebarMenu()
{
    ImGui::BeginChild("##sidebar", ImVec2(180, 0), false, ImGuiWindowFlags_NoScrollbar);

    ImGui::Spacing();
    ImGui::Text(" Lunari Recoil " LUNARI_VERSION);
    ImGui::Separator();
    ImGui::Spacing();

    for (int i = 0; i < 3; i++)
    {
        bool active = (menu_idx == i);

        float target = active ? 1.0f : 0.0f;
        tabAnim[i] = ImLerp(tabAnim[i], target, 0.14f);

        ImVec4 col     = ImLerp(BASE_SURFACE, ACCENT, tabAnim[i]);
        ImVec4 hover   = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 1.0f);
        ImVec4 activeC = ImVec4(ACCENT.x, ACCENT.y, ACCENT.z, 1.0f);

        ImGui::PushStyleColor(ImGuiCol_Button,        col);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hover);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  activeC);

        if (ImGui::Button(tabs[i], ImVec2(-1, 38)))
            menu_idx = i;

        ImGui::PopStyleColor(3);
        ImGui::Spacing();
    }

    ImGui::EndChild();
}