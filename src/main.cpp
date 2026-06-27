#include <iostream>

#include <cmath>

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

    MenuAlpha = ShowMenu
        ? std::min(1.0f, MenuAlpha + 5.0f * dt)
        : std::max(0.0f, MenuAlpha - 5.0f * dt);

    if (MenuAlpha > 0.0f)
    {
        Sidebar();
        Menu();
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