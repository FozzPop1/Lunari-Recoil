#include "../../../inc/gui/LunariImguiFunctions.h"

#include "../../../inc/gui/menu.h"
#include "../../../inc/version.h"
#include "../../../resource/fonts/fontawesome6.h"
#include "../../../inc/macro/config.h"

//------------------------------------------------------------
// Animated display values
//------------------------------------------------------------

static float lerpedRecoilX  = 0.0f;
static float lerpedRecoilY  = 0.0f;
static float lerpedSmoothX  = 0.0f;
static float lerpedSmoothY  = 0.0f;
static float lerpedHumanize = 0.0f;

//------------------------------------------------------------

void RecoilMenu()
{
    if (menu_idx != 0)
        return;

    ImGui::Text(" Recoil Control");
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Checkbox("Enabled", &RecoilToggle);

    ImGui::Spacing();

    DrawLagSlider(
        "##RecoilX",
        &config.RecoilX,
        &lerpedRecoilX,
        -100.f,
        100.f,
        "X: %.1f",
        "Reset##RX",
        0.f);

    DrawLagSlider(
        "##RecoilY",
        &config.RecoilY,
        &lerpedRecoilY,
        -100.f,
        100.f,
        "Y: %.1f",
        "Reset##RY",
        0.f);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextDisabled("Smoothing");
    ImGui::Spacing();

    DrawLagSlider(
        "##SmoothX",
        &config.SmoothingX,
        &lerpedSmoothX,
        0.f,
        0.99f,
        "X: %.2f",
        "Reset##SX",
        0.f);

    DrawLagSlider(
        "##SmoothY",
        &config.SmoothingY,
        &lerpedSmoothY,
        0.f,
        0.99f,
        "Y: %.2f",
        "Reset##SY",
        0.f);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextDisabled("Humanize");
    ImGui::Spacing();

    DrawLagSlider(
        "##Humanize",
        &config.Humanize,
        &lerpedHumanize,
        0.f,
        100.f,
        "%.1f",
        "Reset##H",
        0.f);
}