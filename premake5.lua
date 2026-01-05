workspace "TrEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include Directories --
IncludeDir = {}
IncludeDir["GLFW"] = "TrEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "TrEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "TrEngine/vendor/Imgui"
IncludeDir["glm"] = "TrEngine/vendor/glm"

include "TrEngine/vendor/GLFW"
include "TrEngine/vendor/Glad"
include "TrEngine/vendor/Imgui"

-- ==========================================
-- PROJECT: TrEngine
-- ==========================================
project "TrEngine"
    location "TrEngine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "Tepch.h"
    pchsource "TrEngine/src/Tepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/TrEngine/Platform/OpenGL/ImGuiOpenGLRenderer.h",
        "%{prj.name}/src/TrEngine/Platform/OpenGL/ImGuiOpenGLRenderer.cpp",
        "%{prj.name}/vendor/Imgui/backends/imgui_impl_glfw.h",
        "%{prj.name}/vendor/Imgui/backends/imgui_impl_glfw.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",    
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/GLFW/src",
        "TrEngine/vendor/Imgui/backends",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}", 
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
    }

    -- WINDOWS --
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "_WIN32",
            "_WINDLL",
            "TE_PLATFORM_WINDOWS",
            "TE_BUILD_DLL",
            "IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
            "_GLFW_WIN32",
            "GLFW_EXPOSE_NATIVE_WIN32",
            "GLFW_INCLUDE_NONE",
        }

        links
        {
            "opengl32.lib" 
        }
        -- Post Build Commands Windows
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
        }

    -- LINUX --
    filter "system:linux"
        systemversion "latest"

        defines
        {
            "TE_PLATFORM_LINUX",
            "IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
            "GLFW_INCLUDE_NONE",
            "_GLFW_X11"
        }

        links
        {
            "GL",
            "X11",
            "Xi",
            "Xrandr",
            "Xinerama",
            "Xcursor",
            "pthread",
            "dl"
        }

    filter "configurations:Debug"
        defines "TE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "TE_DIST"
        optimize "On"
    
    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MDd"
    filter { "system:windows", "configurations:Release or Dist" }
        buildoptions "/MD"


-- ==========================================
-- PROJECT: Sandbox
-- ==========================================
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "TrEngine/vendor/spdlog/include",
        "TrEngine/vendor/GLFW/src",
        "TrEngine/src",
        "TrEngine/vendor/Imgui/backends",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",   
    }

    links
    {
        "TrEngine",
    }

    -- WINDOWS --
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "_WIN32",
            "_WINDLL",
            "TE_PLATFORM_WINDOWS",
            "IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
            "_GLFW_WIN32",
            "GLFW_EXPOSE_NATIVE_WIN32",
            "GLFW_INCLUDE_NONE",
        }

    -- LINUX --
    filter "system:linux"
        systemversion "latest"

        defines
        {
            "TE_PLATFORM_LINUX",
            "IMGUI_IMPL_OPENGL_LOADER_CUSTOM",
            "GLFW_INCLUDE_NONE",
            "_GLFW_X11"
        }

    filter "configurations:Debug"
        defines "TE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "TE_DIST"
        optimize "On"

    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MDd"
    filter { "system:windows", "configurations:Release or Dist" }
        buildoptions "/MD"