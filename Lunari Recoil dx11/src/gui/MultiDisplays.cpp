#include "../../inc/gui/window.h"
#include <windows.h>

void Window::GetVirtualDesktopSize(int& width, int& height, int& xPos, int& yPos) {
    xPos = GetSystemMetrics(SM_XVIRTUALSCREEN);
    yPos = GetSystemMetrics(SM_YVIRTUALSCREEN);
    
    // SM_CXVIRTUALSCREEN / SM_CYVIRTUALSCREEN get the total width and height spanning all monitors
    width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
}