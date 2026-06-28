#include "../../inc/macro/macro.h"
#include "../../inc/macro/config.h"
#include "../../inc/macro/recoil.h"

#include "../../inc/gui/menu.h"

#include <windows.h>

void RunMacro() {
    if (RecoilToggle &&
        GetAsyncKeyState(VK_RBUTTON) &&
        GetAsyncKeyState(VK_LBUTTON))
    {
        recoil.MoveMouseRel(config.RecoilX, config.RecoilY, config.SmoothingX, config.SmoothingY, config.Humanize);
    }
}