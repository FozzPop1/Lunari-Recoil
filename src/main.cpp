#include <iostream>

#include "../inc/spoofing/spoof.h"

#include "../inc/version.h"

#include "../inc/gui/window.h"
#include "../inc/gui/menu.h"
#include "../inc/gui/styles.h"

#include "../inc/macro/macro.h"
#include "../inc/macro/config.h"

void Window::WindowLoop() {
    Sidebar();
    Menu();
    RunMacro();
}

int main() {
    InitSpoofs();

    config.SetupConfigFolder();

    window.GetVirtualDesktopSize(window.desktopWidth, window.desktopHeight, window.desktopX, window.desktopY);
    std::cout << "Lunari Recoil - " << LUNARI_VERSION << '\n';

    window.CreateWindowLunari(window.desktopWidth, window.desktopHeight, "Lunari Recoil");
    
    /*
        Setup Gui Style
    */
    DefualtDarkStyle();
    //

    window.StartWindowLoop();


    return 0;
}