workspace "Terran"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Terran/vendor/GLFW/include"
IncludeDir["Glad"] = "Terran/vendor/Glad/include"
IncludeDir["ImGui"] = "Terran/vendor/imgui"
IncludeDir["glm"] = "Terran/vendor/glm"

include "Terran/vendor/GLFW"
include "Terran/vendor/Glad"
include "Terran/vendor/imgui"

project "Terran"
	location "Terran"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Terran/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
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

		defines
		{
			"TR_PLATFORM_WINDOWS",
			"TR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TR_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TR_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TR_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"Terran/vendor/spdlog/include",
		"Terran/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Terran"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TR_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TR_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "TR_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "TR_DIST"
		runtime "Release"
		optimize "On"
