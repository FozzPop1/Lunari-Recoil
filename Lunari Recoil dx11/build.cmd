@echo off
setlocal

echo Compiling resources...
windres resource/icon.rc -O coff -o src/resource.o || goto :error

echo Building...

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
    ext/inc/Imgui/imgui.cpp ^
    ext/inc/Imgui/imgui_draw.cpp ^
    ext/inc/Imgui/imgui_tables.cpp ^
    ext/inc/Imgui/imgui_widgets.cpp ^
    ext/inc/Imgui/imgui_impl_glfw.cpp ^
    ext/inc/Imgui/imgui_impl_win32.cpp ^
    ext/inc/Imgui/imgui_impl_dx11.cpp ^
    -Iinc ^
    -Iext/inc ^
    -Lext/lib ^
    -O2 ^
    -march=x86-64-v2 ^
    -mtune=generic ^
    -fno-exceptions ^
    -fno-rtti ^
    -ffunction-sections ^
    -fdata-sections ^
    -flto=auto ^
    -fno-ident ^
    -fomit-frame-pointer ^
    -fstack-protector-strong ^
    -D_FORTIFY_SOURCE=2 ^
    -fPIE ^
    -DNDEBUG ^
    -DRELEASE_BUILD ^
    -DIMGUI_DISABLE_DEMO_WINDOWS ^
    -DIMGUI_DISABLE_DEBUG_TOOLS ^
    -mwindows ^
    -Wl,-O2 ^
    -Wl,--gc-sections ^
    -Wl,--strip-all ^
    -Wl,--dynamicbase ^
    -Wl,--nxcompat ^
    -Wl,--exclude-libs,ALL ^
    -o "Lunari Recoil.exe" ^
    -lglfw3 ^
    -ld3d11 ^
    -ld3dcompiler ^
    -ldxgi ^
    -ldxguid ^
    -lgdi32 ^
    -luser32 ^
    -lkernel32 ^
    -limm32 ^
    -lshell32 ^
    -lssp

if errorlevel 1 goto :error

echo.
echo Packing binary with UPX...
upx --best --lzma "Lunari Recoil.exe"

echo.
echo ===========================
echo Build completed successfully
echo ===========================
pause
exit /b

:error
echo.
echo ===========================
echo Build FAILED
echo ===========================
pause
exit /b 1