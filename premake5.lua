workspace "LrssnEngine"
    architecture "x64"

    configurations{
        "Debug",
        "Release",
        "Dist"
    }
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "LrssnEngine"
    location "LrssnEngine"
    kind "SharedLib"
    
    language "C++"
    tergetDir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    include{
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines{
            "LE_PLATFORM_WINDOWS",
            "LE_BUILD_DLL"
        }

        postbuildcommands{
            ("{COPY}´%{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    filter "configurations:Debug"
        defines "LE_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "LE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "LE_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    
    language "C++"
    tergetDir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    include{
        "%{prj.name}/vendor/spdlog/include",
        "LrssnEngine/src"
    }

    links{
        "LrssnEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines{
            "LE_PLATFORM_WINDOWS"
        }

      
    filter "configurations:Debug"
        defines "LE_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "LE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "LE_DIST"
        optimize "On"