#include "../../inc/gui/window.h"

#include <iostream>

#include "../../ext/inc/Imgui/imgui.h"
#include "../../ext/inc/Imgui/imgui_impl_glfw.h"
#include "../../ext/inc/Imgui/imgui_impl_opengl3.h"
#include "../../ext/inc/Imgui/imgui_internal.h"

#include "../../inc/gui/menu.h"

// ─────────────────────────────────────────────
// Hide from taskbar
// ─────────────────────────────────────────────
void Window::HideFromTaskbar(GLFWwindow* window)
{
    HWND hwnd = glfwGetWin32Window(window);

    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

    exStyle &= ~WS_EX_APPWINDOW;
    exStyle |= WS_EX_TOOLWINDOW;

    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);

    ShowWindow(hwnd, SW_HIDE);
    ShowWindow(hwnd, SW_SHOW);
}

// ─────────────────────────────────────────────
// Create Window
// ─────────────────────────────────────────────
void Window::CreateWindowLunari(int W, int H, const std::string& title)
{
    if (!glfwInit())
    {
        std::cout << "Failed to init glfw\n";
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    lunari_window = glfwCreateWindow(W, H, title.c_str(), NULL, NULL);

    if (!lunari_window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(lunari_window);
    glfwSwapInterval(1);

    glfwSetWindowPos(lunari_window, desktopX, desktopY);

    // ── IMPORTANT: store HWND ONCE ──
    hwnd = glfwGetWin32Window(lunari_window);

    // ── Apply Windows effects ──
    HideFromTaskbar(lunari_window);

    glfwShowWindow(lunari_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        exit(-1);
    }

    // ─────────────────────────────
    // ImGui setup
    // ─────────────────────────────
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    io.Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\segoeui.ttf",
        18.0f
    );

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(lunari_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glViewport(0, 0, W, H);
}

// ─────────────────────────────────────────────
// Click-through toggle
// ─────────────────────────────────────────────
void Window::SetClickThrough(GLFWwindow* window, bool enable)
{
    HWND hwnd = glfwGetWin32Window(window);

    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);

    if (enable)
        exStyle |= WS_EX_TRANSPARENT | WS_EX_LAYERED;
    else
        exStyle &= ~WS_EX_TRANSPARENT;

    exStyle &= ~WS_EX_APPWINDOW;
    exStyle |= WS_EX_TOOLWINDOW;

    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);

    clickThroughStateDirty = true;
}

// ─────────────────────────────────────────────
// Detect ImGui hover & toggle click-through
// ─────────────────────────────────────────────
void Window::UpdateClickThrough(GLFWwindow* window)
{
    static bool lastState = false;

    POINT cursor;
    GetCursorPos(&cursor);

    int winX, winY, winW, winH;
    glfwGetWindowPos(window, &winX, &winY);
    glfwGetWindowSize(window, &winW, &winH);

    bool overImGui = false;

    if (cursor.x >= winX && cursor.x <= winX + winW &&
        cursor.y >= winY && cursor.y <= winY + winH)
    {
        float localX = (float)(cursor.x - winX);
        float localY = (float)(cursor.y - winY);

        ImGuiContext* ctx = ImGui::GetCurrentContext();

        for (ImGuiWindow* imWin : ctx->Windows)
        {
            if (!imWin->Active || imWin->Hidden)
                continue;

            if (imWin->Flags & ImGuiWindowFlags_ChildWindow)
                continue;

            ImVec2 wMin = imWin->Pos;
            ImVec2 wMax = ImVec2(imWin->Pos.x + imWin->Size.x,
                                 imWin->Pos.y + imWin->Size.y);

            if (localX >= wMin.x && localX <= wMax.x &&
                localY >= wMin.y && localY <= wMax.y)
            {
                overImGui = true;
                break;
            }
        }
    }

    if (overImGui == lastState && !clickThroughStateDirty)
        return;

    lastState = overImGui;
    clickThroughStateDirty = false;

    SetClickThrough(window, !overImGui);

    if (overImGui)
    {
        HWND hwndLocal = glfwGetWin32Window(window);

        DWORD fgThread = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
        DWORD myThread = GetCurrentThreadId();

        if (fgThread != myThread)
            AttachThreadInput(fgThread, myThread, TRUE);

        BringWindowToTop(hwndLocal);
        SetActiveWindow(hwndLocal);
        SetForegroundWindow(hwndLocal);

        if (fgThread != myThread)
            AttachThreadInput(fgThread, myThread, FALSE);
    }
}

// ─────────────────────────────────────────────
// Main loop
// ─────────────────────────────────────────────
void Window::StartWindowLoop()
{
    while (running)
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        WindowLoop();

        if (!ClickThroughWindow)
            UpdateClickThrough(lunari_window);
        else
            SetClickThrough(lunari_window, true);

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(lunari_window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(lunari_window);
    glfwTerminate();
}

// ─────────────────────────────────────────────
Window window;