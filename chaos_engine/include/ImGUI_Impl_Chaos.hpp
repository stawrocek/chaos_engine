#ifndef IMGUI_IMPL_CHAOS_HPP
#define IMGUI_IMPL_CHAOS_HPP

#include "Export.hpp"
#include <iostream>

#include "Window.hpp"
#include "Logger.hpp"
#include "Shader.hpp"

#include "imgui/imgui.h"

struct SDL_Window;
typedef union SDL_Event SDL_Event;

CHAOS_EXPORT bool           ImGui_ImplChaos_Init(SDL_Window*);
CHAOS_EXPORT void           ImGui_ImplChaos_Shutdown();
CHAOS_EXPORT void           ImGui_ImplChaos_NewFrame(SDL_Window* window);
CHAOS_EXPORT bool           ImGui_ImplChaos_ProcessEvent(SDL_Event* event);

// Use if you want to reset your rendering device without losing ImGui state.
CHAOS_EXPORT void           ImGui_ImplChaos_InvalidateDeviceObjects();
CHAOS_EXPORT bool           ImGui_ImplChaos_CreateDeviceObjects();

#endif //IMGUI_IMPL_CHAOS_HPP




