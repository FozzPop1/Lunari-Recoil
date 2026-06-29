#include "../../inc/gui/window.h"

#include <iostream>

#include "../../ext/inc/Imgui/imgui.h"
#include "../../ext/inc/Imgui/imgui_internal.h"
#include "../../ext/inc/Imgui/imgui_impl_glfw.h"
#include "../../ext/inc/Imgui/imgui_impl_dx11.h"

#include "../../resource/fonts/fontawesome6.h"
#include "../../resource/fonts/Inter_18pt-Regular.h"
#include "../../resource/fonts/Inter_18pt-SemiBold.h"
#include "../../resource/fonts/fa-solid-900.h"

#include "../../inc/gui/menu.h"

ImFont* FontRegular  = nullptr;
ImFont* FontSemiBold = nullptr;
ImFont* FontAwesome  = nullptr;

static ID3D11Device*            g_pd3dDevice           = nullptr;
static ID3D11DeviceContext*     g_pd3dDeviceContext    = nullptr;
static IDXGISwapChain*          g_pSwapChain           = nullptr;
static ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;

static void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer = nullptr;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

static void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

static bool CreateDeviceD3D(HWND hwnd, int W, int H)
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount                        = 2;
    sd.BufferDesc.Width                   = W;
    sd.BufferDesc.Height                  = H;
    sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator   = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow                       = hwnd;
    sd.SampleDesc.Count                   = 1;
    sd.Windowed                           = TRUE;
    sd.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        nullptr, 0, D3D11_SDK_VERSION,
        &sd, &g_pSwapChain, &g_pd3dDevice, nullptr, &g_pd3dDeviceContext
    );

    if (FAILED(hr)) return false;

    CreateRenderTarget();
    return true;
}

static void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain)        { g_pSwapChain->Release();        g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice)        { g_pd3dDevice->Release();        g_pd3dDevice = nullptr; }
}

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

    glfwWindowHint(GLFW_CLIENT_API,             GLFW_NO_API);   // no OpenGL
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED,              GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING,               GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE,              GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE,                GLFW_FALSE);

    lunari_window = glfwCreateWindow(W, H, title.c_str(), NULL, NULL);

    if (!lunari_window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwSetWindowPos(lunari_window, desktopX, desktopY);

    hwnd = glfwGetWin32Window(lunari_window);

    // Make it overlay/topmost
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    HideFromTaskbar(lunari_window);
    glfwShowWindow(lunari_window);

    // Init D3D11
    if (!CreateDeviceD3D(hwnd, W, H))
    {
        std::cout << "Failed to create D3D11 device\n";
        exit(-1);
    }

    // ─────────────────────────────
    // ImGui setup
    // ─────────────────────────────
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

    ImFontConfig regularConfig;
    regularConfig.FontDataOwnedByAtlas = false;

    ImFontConfig semiBoldConfig;
    semiBoldConfig.FontDataOwnedByAtlas = false;

    ImFontConfig iconConfig;
    iconConfig.FontDataOwnedByAtlas  = false;
    iconConfig.MergeMode             = true;
    iconConfig.GlyphMinAdvanceX      = 18.0f;
    iconConfig.GlyphMaxAdvanceX      = 18.0f;
    iconConfig.PixelSnapH            = true;
    iconConfig.GlyphOffset           = ImVec2(0.0f, 2.0f);

    FontRegular = io.Fonts->AddFontFromMemoryTTF(
        (void*)Inter_18ptRegular, sizeof(Inter_18ptRegular), 18.0f, &regularConfig);
    io.Fonts->AddFontFromMemoryTTF(
        (void*)fasolid900, sizeof(fasolid900), 18.0f, &iconConfig, icon_ranges);

    FontSemiBold = io.Fonts->AddFontFromMemoryTTF(
        (void*)Inter_18ptSemiBold, sizeof(Inter_18ptSemiBold), 18.0f, &semiBoldConfig);
    io.Fonts->AddFontFromMemoryTTF(
        (void*)fasolid900, sizeof(fasolid900), 18.0f, &iconConfig, icon_ranges);

    io.Fonts->Build();

    ImGui::StyleColorsDark();

    // D3D11 backends — note InitForOther since we're not using OpenGL
    ImGui_ImplGlfw_InitForOther(lunari_window, true);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
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
            if (!imWin->Active || imWin->Hidden)         continue;
            if (imWin->Flags & ImGuiWindowFlags_ChildWindow) continue;

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

        // Clear with full transparency
        const float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clearColor);
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        WindowLoop();

        if (!ClickThroughWindow)
            UpdateClickThrough(lunari_window);
        else
            SetClickThrough(lunari_window, true);

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // replaces glfwSwapBuffers
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();

    glfwDestroyWindow(lunari_window);
    glfwTerminate();
}

// ─────────────────────────────────────────────
Window window;