#include "../../inc/gui/window.h"

#include <iostream>

#include "../../ext/inc/Imgui/imgui.h"
#include "../../ext/inc/Imgui/imgui_impl_glfw.h"
#include "../../ext/inc/Imgui/imgui_impl_opengl3.h"

void Window::CreateWindowLunari(int W, int H, const std::string &title) {
    
    /*
        Window Setup
    */
   
    if (!glfwInit()) {
        std::cout << "Failed to init glfw" << '\n';
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);      // Remove borders/title bar
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // Enable alpha blending
    //glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);         // Always on top
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);      // Prevent manual dragging to resize
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    
    lunari_window = glfwCreateWindow(W, H, title.c_str(), NULL, NULL);

    if (lunari_window == NULL) {
        std::cout << "Failed to make window" << '\n';
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(lunari_window);
    glfwSwapInterval(1); 
    
    glfwSetWindowPos(lunari_window, Window::desktopX, Window::desktopY);
    glfwShowWindow(lunari_window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        exit(-1);
    }

    /*
        ImGui Setup
    */

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImFont* myFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(lunari_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glViewport(0, 0, W, H);
}

void Window::StartWindowLoop() {
while (running) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    WindowLoop();

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

Window window;