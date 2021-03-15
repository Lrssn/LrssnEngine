include "vendors/premake/premake_customization/solution_items.lua"

workspace "LrssnEngine"
	architecture "x86_64"
	startproject "LrssnEngine-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/LrssnEngine/vendors/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/LrssnEngine/vendors/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/LrssnEngine/vendors/imgui"
IncludeDir["glm"] = "%{wks.location}/LrssnEngine/vendors/glm"
IncludeDir["stb_image"] = "%{wks.location}/LrssnEngine/vendors/stb_image"
IncludeDir["entt"] = "%{wks.location}/LrssnEngine/vendors/entt/single_include/entt"
IncludeDir["yaml_cpp"] = "%{wks.location}/LrssnEngine/vendors/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/LrssnEngine/vendors/ImGuizmo"

group "Dependencies"
	include "vendors/premake"
	include "LrssnEngine/vendors/GLFW"
	include "LrssnEngine/vendors/Glad"
	include "LrssnEngine/vendors/imgui"
	include "LrssnEngine/vendors/yaml-cpp"
group ""

include "LrssnEngine"
include "Sandbox"
include "LrssnEngine-Editor"