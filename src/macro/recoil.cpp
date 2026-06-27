#include "../../inc/macro/recoil.h"

#include <windows.h>

/*
    Function to move the mouse
*/

void Recoil::MoveMouseRel(float x, float y) {
    static float accumX = 0.f, accumY = 0.f;

    accumX += x;
    accumY += y;

    LONG dx = static_cast<LONG>(accumX);
    LONG dy = static_cast<LONG>(accumY);

    accumX -= dx;
    accumY -= dy;

    if (dx == 0 && dy == 0) return;

    INPUT input = {};
    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    SendInput(1, &input, sizeof(INPUT));
}

Recoil recoil;