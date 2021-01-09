workspace "Drifter-Engine"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["glfw"] = "vendors/glfw/include"
	IncludeDir["glad"] = "vendors/glad/include"
	IncludeDir["imgui"] = "vendors/imgui"
	IncludeDir["glm"] = "vendors/glm"
	IncludeDir["stb_image"] = "vendors/stb_image"

group "Dependencies"
	include "/vendors/glfw"
	include "/vendors/glad"
	include "/vendors/imgui"

group ""

project "Drifter-Engine"
	location "Drifter-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "dfpch.h"
	pchsource "%{prj.name}/src/dfpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"vendors/glm/glm/**.cpp",
		"vendors/stb_image/**.h",
		"vendors/stb_image/**.cpp",
	}

	defines{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs{
		"%{prj.name}/src",
		"vendors/spdlogger/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}

	links{
		"glfw",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines{
			"DF_CORE",
			"DF_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DF_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DF_DIST"
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
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"vendors/spdlogger/include",
		"Drifter-Engine/src",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Drifter-Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"DF_CLIENT",
			"DF_PLATFORM_WINDOWS"
		}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DF_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DF_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DF_DIST"
		runtime "Release"
		optimize "on"