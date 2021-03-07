workspace "LrssnEngine"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["Spdlog"] = "LrssnEngine/vendors/spdlog/include"
IncludeDir["GLFW"] = "LrssnEngine/vendors/GLFW/include"
IncludeDir["Glad"] = "LrssnEngine/vendors/Glad/include"
IncludeDir["ImGui"] = "LrssnEngine/vendors/ImGui"
IncludeDir["Glm"] = "LrssnEngine/vendors/Glm"
IncludeDir["stb_image"] = "LrssnEngine/vendors/stb_image"

group "Dependencies"
    include "LrssnEngine/vendors/GLFW"
    include "LrssnEngine/vendors/Glad"
    include "LrssnEngine/vendors/ImGui"

group ""

project "LrssnEngine"
    location "LrssnEngine"
    kind "StaticLib"
    
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lepch.h"
    pchsource "LrssnEngine/src/lepch.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendors/stb_image/**.h",
		"%{prj.name}/vendors/stb_image/**.cpp",
        "%{prj.name}/vendors/Glm/glm/**.hpp",
		"%{prj.name}/vendors/Glm/glm/**.inl",
    }
    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
    includedirs{
        "%{prj.name}/src",
        "%{IncludeDir.Spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.Glm}",
        "%{IncludeDir.stb_image}"
    }

    links 
	{ 
		"GLFW",
        "Glad",
        "ImGui",
		"opengl32.lib"
	}

    filter "system:windows"
        systemversion "latest"
        
        defines{
            "LE_PLATFORM_WINDOWS",
            "LE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LE_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    
    language "C++"
	cppdialect "C++17"
    staticruntime "on"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "%{IncludeDir.Spdlog}",
        "LrssnEngine/src",
        "LrssnEngine/vendors",
        "%{IncludeDir.Glm}"
    }

    links{
        "LrssnEngine"
    }

    filter "system:windows"
        systemversion "latest"
        
        defines{
            "LE_PLATFORM_WINDOWS"
        }

      
    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LE_DIST"
        runtime "Release"
        optimize "on"