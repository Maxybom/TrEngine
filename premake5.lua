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

IncludeDir = {}
IncludeDir["GLFW"] = "TrEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "TrEngine/vendor/glad/include"
IncludeDir["ImGui"] = "TrEngine/vendor/Imgui"

include "TrEngine/vendor/GLFW"
include "TrEngine/vendor/Glad"
include "TrEngine/vendor/Imgui"

project "TrEngine"
    location "TrEngine"
    kind "SharedLib"
    language "C++"

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
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/GLFW/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "TrEngine/vendor/Imgui/backends"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "Imgui",
        "opengl32.lib",
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
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

    postbuildcommands
    {
        ("IF NOT EXIST ..\\bin\\" .. outputdir .. "\\Sandbox\\TrEngine.dll (xcopy /Q /Y /I ..\\bin\\" .. outputdir .. "\\TrEngine\\TrEngine.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul)")
    }

    filter "configurations:Debug"
        defines "TE_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "TE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "TE_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "TrEngine/src",
        "TrEngine/vendor/Imgui/backends"
    }

    links
    {
        "TrEngine",
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
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

    postbuildcommands
    {
        ("IF NOT EXIST ..\\bin\\" .. outputdir .. "\\Sandbox\\Sandbox.exe (xcopy /Q /Y /I ..\\bin\\" .. outputdir .. "\\Sandbox\\Sandbox.exe ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul)")
    }

    filter "configurations:Debug"
        defines "TE_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "TE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "TE_DIST"
        buildoptions "/MD"
        optimize "On"
