#pragma once

#include <string>

#include "../../ext/inc/glad/glad.h"
#include "../../ext/inc/GLFW/glfw3.h"

class Window {
    private:

    GLFWwindow* lunari_window;

    public:

    bool running = true;

    void CreateWindowLunari(int Width, int Height, const std::string &title);
    void WindowLoop();
    void StartWindowLoop();
    void GetVirtualDesktopSize(int& width, int& height, int& xPos, int& yPos);

    int desktopX, desktopY, desktopWidth, desktopHeight;
};

extern Window window;