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

	include "/vendors/glfw"
	include "/vendors/glad"
	include "/vendors/imgui"

project "Drifter-Engine"
	location "Drifter-Engine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"vendors/spdlogger/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
	}

	links{
		"glfw",
		"glad",
		"imgui",
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
		symbols "On"

	filter "configurations:Release"
		defines "DF_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DF_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"vendors/spdlogger/include",
		"Drifter-Engine/src"
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
		symbols "On"

	filter "configurations:Release"
		defines "DF_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "DF_DIST"
		runtime "Release"
		optimize "On"