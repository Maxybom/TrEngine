#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <TrEngine/Platform/OpenGL/ImGuiOpenGLRenderer.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>

#include "TrEngine/Log.h"

#ifdef TE_PLATFORM_WINDOWS
#include "Windows.h"
#endif // TE_PLATFORM_WINDOWS
