#define NOMINMAX

#include <iostream>

#include <cmath>
#include <algorithm>

#include "../inc/security/process_security.h"
#include "../inc/spoofing/spoof.h"
#include "../inc/version.h"
#include "../inc/gui/window.h"
#include "../inc/gui/menu.h"
#include "../inc/gui/styles.h"
#include "../inc/macro/macro.h"
#include "../inc/macro/config.h"

static bool insertPressed = false;

void Window::WindowLoop()
{
    // Toggle on INSERT press
    if (GetAsyncKeyState(VK_INSERT) & 0x8000)
    {
        if (!insertPressed)
        {
            insertPressed = true;
            ShowMenu = !ShowMenu;
            ClickThroughWindow = !ShowMenu;
        }
    }
    else
    {
        insertPressed = false;
    }

    float dt = ImGui::GetIO().DeltaTime;

    // Exponential ease — fast start, smooth finish
    float target = ShowMenu ? 1.0f : 0.0f;
    MenuAlpha += (target - MenuAlpha) * (1.0f - std::exp(-12.0f * dt));
    MenuAlpha = std::clamp(MenuAlpha, 0.0f, 1.0f);

    if (MenuAlpha > 0.004f) // ~1/255, below visible threshold
    {
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, MenuAlpha);
        //Sidebar();
        Menu();
        //RecoilPreview();
        ImGui::PopStyleVar();
        ImGui::GetStyle().Alpha = MenuAlpha;
    }

    RunMacro();
}

int main()
{
    ProcessSecurity::EnableMitigations();



    config.SetupConfigFolder();

    window.GetVirtualDesktopSize(
        window.desktopWidth,
        window.desktopHeight,
        window.desktopX,
        window.desktopY
    );

#ifdef _DEBUG
    std::cout << "Lunari Recoil - " << LUNARI_VERSION << '\n';
#endif

    window.CreateWindowLunari(
        window.desktopWidth,
        window.desktopHeight,
        "Lunari Recoil"
    );

    DefualtDarkStyle();

    window.StartWindowLoop();

    return 0;
}