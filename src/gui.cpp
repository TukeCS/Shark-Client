#include "gui.h"

#include "imgui_hook.h"
#include "imgui.h"
#include <Windows.h>

extern HMODULE g_hModule;
extern bool g_isDetached;
extern DWORD WINAPI ExitThread(LPVOID lpThreadParameter);

namespace gui
{
    // This function is called once when the hook is initialized
    // You can use it to set up ImGui styles, fonts, etc.
    void initializeImGui()
    {
        ImGui::StyleColorsDark();
    }

    // This function is called every frame to render the ImGui interface
    // You can use it to create windows, buttons, sliders, etc.
    void renderImGui()
    {
        ImGui::Begin("Menu");
        ImGui::Text("If you see this, everything is working fine");
        ImGui::End();
    }

    // Initialize the ImGui hook with the render and init functions
    void initializeHook()
    {
        if (!ImGuiHook::Load(renderImGui, initializeImGui))
        {
            // Failed to load the ImGui hook!
            // You can use ImGuiHook::GetLastError() to get the last error message
            // Handle the error here, e.g., log it or show a message box
        }
    }
}