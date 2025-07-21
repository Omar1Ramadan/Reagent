workspace "Reagent"
    architecture "x64"
    
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder
IncludeDir = {}
IncludeDir ["GLFW"] = "Reagent/etc/GLFW/include"

include "Reagent/etc/GLFW/premake5.lua"

project "Reagent"
    location "Reagent"
    kind "SharedLib"
    language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rgpch.h"
    pchsource "Reagent/src/rgpch.cpp"

    forceincludes { "rgpch.h" }

    files
    {
        "src/**.h",
        "src/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "src",
        "%{prj.name}/src",
        "src/Platform/Windows",
        "%{prj.name}/etc/spdlog/include",
        "$(VC_IncludePath)",
        "%{IncludeDir.GLFW}"
    }
    links
    {
        "GLFW",
        "opengl32.lib", -- Link against OpenGL library
    }

    buildoptions { "/utf-8"}

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "RG_WINDOWS",
            "RG_DLL"
        }

        postbuildcommands
        {
            -- Ensure target directory exists first
            "mkdir ../bin/" .. outputdir .. "/Sandbox 2>nul",
            -- Then copy the DLL file there
            "{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/"
        }

    filter "configurations:Debug"
        defines { "RG_DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "RG_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "RG_DIST" }
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Sandbox/**.h",
        "Sandbox/**.cpp"
    }

    includedirs
    {
        "Reagent/etc/spdlog/include",
    }

    buildoptions { "/utf-8"}

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "RG_WINDOWS",
            "RG_ENTRY"
        }

    links
    {
        "Reagent"
    }

    filter "configurations:Debug"
        defines { "RG_DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "RG_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "RG_DIST" }
        optimize "On"
