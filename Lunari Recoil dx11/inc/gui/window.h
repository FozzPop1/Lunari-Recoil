#pragma once

#include <string>
#include <windows.h>
#include <d3d11.h>

#include "../../ext/inc/GLFW/glfw3.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "../../ext/inc/GLFW/glfw3native.h"

class Window {
private:
    GLFWwindow* lunari_window = nullptr;

public:
    HWND hwnd = nullptr;

    bool running             = true;
    bool ClickThroughWindow  = false;
    bool clickThroughStateDirty = false;

    int desktopX      = 0;
    int desktopY      = 0;
    int desktopWidth  = 0;
    int desktopHeight = 0;

    void CreateWindowLunari(int Width, int Height, const std::string& title);
    void StartWindowLoop();
    void WindowLoop();

    void GetVirtualDesktopSize(int& width, int& height, int& xPos, int& yPos);
    void SetClickThrough(GLFWwindow* window, bool enable);
    void UpdateClickThrough(GLFWwindow* window);
    void HideFromTaskbar(GLFWwindow* window);
};

extern Window window;