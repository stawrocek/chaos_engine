#ifndef IMGUI_IMPL_CHAOS_HPP
#define IMGUI_IMPL_CHAOS_HPP

#include "../include/Export.hpp"
#include <iostream>

#include "../include/Window.hpp"
#include "../include/Logger.hpp"
#include "../include/Shader.hpp"
#include "../include/Event.hpp"

#include "../include/imgui/imgui.h"

CHAOS_EXPORT bool           ImGui_ImplChaos_Init(chaos::Window*);
CHAOS_EXPORT void           ImGui_ImplChaos_Shutdown();
CHAOS_EXPORT void           ImGui_ImplChaos_NewFrame(chaos::Window* window);
CHAOS_EXPORT bool           ImGui_ImplChaos_ProcessEvent(chaos::Event*, chaos::InputManager*);

// Use if you want to reset your rendering device without losing ImGui state.
CHAOS_EXPORT void           ImGui_ImplChaos_InvalidateDeviceObjects();
CHAOS_EXPORT bool           ImGui_ImplChaos_CreateDeviceObjects();

#endif //IMGUI_IMPL_CHAOS_HPP




