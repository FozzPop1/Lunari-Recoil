#pragma once

#include <string>

#include "../../ext/inc/glad/glad.h"

#define GLFW_EXPOSE_NATIVE_WIN32

#include "../../ext/inc/GLFW/glfw3.h"
#include "../../ext/inc/GLFW/glfw3native.h"

#include <windows.h>

class Window {
    private:

    GLFWwindow* lunari_window;

    HWND hwnd;
    LONG style;

    public:

    bool running = true;
    bool ClickThroughWindow;

    void CreateWindowLunari(int Width, int Height, const std::string &title);
    void WindowLoop();
    void StartWindowLoop();
    void GetVirtualDesktopSize(int& width, int& height, int& xPos, int& yPos);
    void SetClickThrough(GLFWwindow* window, bool enable);

    int desktopX, desktopY, desktopWidth, desktopHeight;
};

extern Window window;