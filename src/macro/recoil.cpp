#include "../../inc/macro/recoil.h"

#include <windows.h>
#include <cmath>
#include <algorithm>

/*
    Function to move the mouse
*/

void Recoil::MoveMouseRel(float x, float y)
{
    static float accumX = 0.0f;
    static float accumY = 0.0f;

    accumX += x;
    accumY += y;

    LONG dx = static_cast<LONG>(accumX);
    LONG dy = static_cast<LONG>(accumY);

    accumX -= static_cast<float>(dx);
    accumY -= static_cast<float>(dy);

    if (dx | dy)
        mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(dx), static_cast<DWORD>(dy), 0, 0);
}

Recoil recoil;