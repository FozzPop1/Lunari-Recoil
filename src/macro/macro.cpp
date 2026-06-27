#include "../../inc/macro/macro.h"
#include "../../inc/macro/config.h"
#include "../../inc/macro/recoil.h"

#include "../../inc/gui/menu.h"

#include <windows.h>

void RunMacro() {
    if (RecoilToggle == true) {
        if (GetAsyncKeyState(VK_RBUTTON)) {
            if (GetAsyncKeyState(VK_LBUTTON)) {
                recoil.MoveMouseRel(config.RecoilX, config.RecoilY);
            }
        }
    }
}