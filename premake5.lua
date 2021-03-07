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


include "LrssnEngine/vendors/GLFW"
include "LrssnEngine/vendors/Glad"
include "LrssnEngine/vendors/ImGui"


project "LrssnEngine"
    location "LrssnEngine"
    kind "SharedLib"
    
    language "C++"
    staticruntime "off"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "lepch.h"
    pchsource "LrssnEngine/src/lepch.cpp"

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendors/Glm/glm/**.hpp",
		"%{prj.name}/vendors/Glm/glm/**.inl",
    }

    includedirs{
        "%{prj.name}/src",
        "%{IncludeDir.Spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.Glm}"
    }

    links 
	{ 
		"GLFW",
        "Glad",
        "ImGui",
		"opengl32.lib"
	}

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        defines{
            "LE_PLATFORM_WINDOWS",
            "LE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "LE_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    
    language "C++"
    staticruntime "off"
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
        cppdialect "C++17"
        systemversion "latest"
        
        defines{
            "LE_PLATFORM_WINDOWS"
        }

      
    filter "configurations:Debug"
        defines "LE_DEBUG"
        runtime "Debug"
        symbols "On"
    
    filter "configurations:Release"
        defines "LE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "LE_DIST"
        runtime "Release"
        optimize "On"