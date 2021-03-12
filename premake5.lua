workspace "LrssnEngine"
    architecture "x86_64"
    startproject "LrssnEngine-Editor"
    configurations{
        "Debug",
        "Release",
        "Dist"
    }
    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["Spdlog"] = "LrssnEngine/vendors/spdlog/include"
IncludeDir["GLFW"] = "LrssnEngine/vendors/GLFW/include"
IncludeDir["Glad"] = "LrssnEngine/vendors/Glad/include"
IncludeDir["ImGui"] = "LrssnEngine/vendors/ImGui"
IncludeDir["Glm"] = "LrssnEngine/vendors/Glm"
IncludeDir["stb_image"] = "LrssnEngine/vendors/stb_image"
IncludeDir["entt"] = "LrssnEngine/vendors/entt/single_include/entt"

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
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}
    includedirs{
        "%{prj.name}/src",
        "%{IncludeDir.Spdlog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.Glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}"
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
        "%{IncludeDir.Glm}",
        "%{IncludeDir.entt}"
    }

    links{
        "LrssnEngine"
    }

    filter "system:windows"
        systemversion "latest"

      
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

        
project "LrssnEngine-Editor"
    location "LrssnEngine-Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "LrssnEngine/vendors/spdlog/include",
        "LrssnEngine/src",
        "LrssnEngine/vendors",
        "%{IncludeDir.Glm}",
        "%{IncludeDir.entt}"
    }

    links
    {
        "LrssnEngine"
    }

    filter "system:windows"
        systemversion "latest"

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