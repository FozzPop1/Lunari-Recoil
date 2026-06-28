#include "../../../inc/gui/menu.h"
#include "../../../inc/gui/window.h"

void SettingsMenu() {
    if (menu_idx == 2)
    {
        if (ImGui::Button("Exit"))
            window.running = false;
    }
}