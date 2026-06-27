windres resource/icon.rc -O coff -o src/resource.o

g++ -std=c++17 src/main.cpp ^
    src/resource.o ^
    src/macro/config.cpp ^
    src/macro/recoil.cpp ^
    src/macro/macro.cpp ^
    src/gui/window.cpp ^
    src/gui/menu.cpp ^
    src/gui/MultiDisplays.cpp ^
    src/gui/styles.cpp ^
    src/gui/background_effect.cpp ^
    ext/inc/glad.c ^
    ext/inc/Imgui/imgui_demo.cpp ^
    ext/inc/Imgui/imgui_draw.cpp ^
    ext/inc/Imgui/imgui_impl_glfw.cpp ^
    ext/inc/Imgui/imgui_impl_opengl3.cpp ^
    ext/inc/Imgui/imgui_tables.cpp ^
    ext/inc/Imgui/imgui_widgets.cpp ^
    ext/inc/Imgui/imgui.cpp ^
    -I inc -I ext/inc ^
    -L ext/lib ^
    -o "Lunari Recoil" ^
    -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 -limm32 -lshell32 -lntdll

pause