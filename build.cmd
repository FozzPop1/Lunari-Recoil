windres resource/icon.rc -O coff -o src/resource.o

g++ -std=c++17 ^
    src/main.cpp ^
    src/resource.o ^
    src/macro/config.cpp ^
    src/macro/recoil.cpp ^
    src/macro/macro.cpp ^
    src/gui/window.cpp ^
    src/gui/menu.cpp ^
    src/gui/MultiDisplays.cpp ^
    src/gui/styles.cpp ^
    src/gui/background_effect.cpp ^
    src/gui/menus/configs.cpp ^
    src/gui/menus/recoil.cpp ^
    src/gui/menus/settings.cpp ^
    src/gui/menus/sidebar.cpp ^
    src/gui/menus/RecoilPreview.cpp ^
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
    -O2 ^
    -march=native ^
    -mtune=native ^
    -ffast-math ^
    -fno-exceptions ^
    -fno-rtti ^
    -ffunction-sections ^
    -fdata-sections ^
    -flto=auto ^
    -fno-ident ^
    -fomit-frame-pointer ^
    -DNDEBUG ^
    -DIMGUI_DISABLE_DEMO_WINDOWS ^
    -DIMGUI_DISABLE_DEBUG_TOOLS ^
    -mwindows ^
    -Wl,--gc-sections ^
    -Wl,--strip-all ^
    -Wl,-O2 ^
    -o "Lunari Recoil.exe" ^
    -lglfw3 -lopengl32 -lgdi32 -luser32 -lkernel32 -limm32 -lshell32 -lntdll -lssp

pause