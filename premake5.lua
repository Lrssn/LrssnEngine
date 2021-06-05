include "vendors/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"
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