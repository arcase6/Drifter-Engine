workspace "Drifter-Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["glfw"] = "vendors/glfw/include"
	IncludeDir["glad"] = "vendors/glad/include"
	IncludeDir["imgui"] = "vendors/imgui"
	IncludeDir["glm"] = "vendors/glm"
	IncludeDir["stb_image"] = "vendors/stb_image"
	IncludeDir["fmt"] = "vendors/fmt/include"

	include "/vendors/glfw"
	include "/vendors/glad"
	include "/vendors/imgui"
	include "/vendors/fmt"

project "Drifter-Engine"
	location "Drifter-Engine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"vendors/glm/glm/**.cpp",
		"vendors/stb_image/**.h",
		"vendors/stb_image/**.cpp",
	}

	defines{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs{
		"%{prj.name}/src",
		"vendors/spdlogger/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.fmt}"
	}

	links{
		"glfw",
		"glad",
		"imgui",
		"fmt",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"DF_CORE",
			"DF_PLATFORM_WINDOWS",
			"DRIFTER_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines {
			"DF_DEBUG",
			"DF_ENABLE_ASSERTS"
		}
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.fmt}"
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