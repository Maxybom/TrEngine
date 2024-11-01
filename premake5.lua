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

project "TrEngine"
    location "TrEngine"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "TrEngine/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "_WINDLL",
            "TE_PLATFORM_WINDOWS",
            "TE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("IF NOT EXIST ..\\bin\\" .. outputdir .. "\\Sandbox\\TrEngine.dll (xcopy /Q /Y /I ..\\bin\\" .. outputdir .. "\\TrEngine\\TrEngine.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul)")
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

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "TrEngine/vendor/spdlog/include",
        "TrEngine/src"
    }

    links
    {
        "TrEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "_WINDLL",
            "TE_PLATFORM_WINDOWS",
        }

        postbuildcommands
        {
            ("IF NOT EXIST ..\\bin\\" .. outputdir .. "\\Sandbox\\Sandbox.exe (xcopy /Q /Y /I ..\\bin\\" .. outputdir .. "\\Sandbox\\Sandbox.exe ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul)")
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
