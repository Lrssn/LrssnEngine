project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
        "src/**.hpp",
        "src/**.c",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/LrssnEngine/vendors/spdlog/include",
		"%{wks.location}/LrssnEngine/src",
		"%{wks.location}/LrssnEngine/vendors",
		"%{IncludeDir.glm}",
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