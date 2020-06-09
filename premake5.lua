-- TODO: Add support for MAC OS and Linux

workspace "Nova"		-- "Solution name"
	architecture "x64"	-- Only support x64

	configurations
	{
		"Debug",		-- Development
		"Release",		-- "Faster development", still logging etc
		"Dist"			-- For release to "other people", stripped version
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Nova {Engine} Project
project "Nova"
	location "Nova"
	kind "SharedLib"	-- == "DLL" in Windows
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- Precompiled header for Nova project
	pchheader "novapch.h"
	pchsource "Nova/src/novapch.cpp"	-- Only needed for Visual Studio (MSVC Compiler) (needs full path)

	files
	{
		-- Add more files if needed, other file extensions etc
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		-- Add more include folders if needed, other 3rd party etc
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	-- WINDOWS
	filter "system:windows"			 -- Everything below here, until next "filter" or "project" is Windows-only
		cppdialect "C++17"			 -- "Only works" for Win, for other OS, flags etc might be needed
		staticruntime "On"			 -- Link statically
		systemversion "latest"		 -- You could use "latest" as well (Windows SDK)

		defines
		{
			-- Windows specific DEFINES, add/remove as needed
			"NOVA_PLATFORM_WINDOWS",
			"NOVA_BUILD_DLL"
		}

		postbuildcommands
		{
			-- TODO: Move this to Nebulas project instead, wierd that Nova project should know about Nebula
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Nebula")
		}
	
	filter "configurations:Debug"
		defines "NOVA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NOVA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NOVA_DIST"
		optimize "On"

-- Nebula {Sandbox} Project
project "Nebula"
	location "Nebula"
	kind "ConsoleApp" -- Executable (.exe on Windows)
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		-- Add more files if needed, other file extensions etc
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		-- Add more include folders if needed, other 3rd party etc
		"Nova/vendor/spdlog/include",
		"Nova/src"
	}

	links
	{
		"Nova"
	}

	-- WINDOWS
	filter "system:windows"			 -- Everything below here, until next "filter" or "project" is Windows-only
		cppdialect "C++17"			 -- "Only works" for Win, for other OS, flags etc might be needed
		staticruntime "On"			 -- Link statically
		systemversion "latest"       -- You could use "latest" as well (Windows SDK)

		defines
		{
			-- Windows specific DEFINES, add/remove as needed
			"NOVA_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "NOVA_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NOVA_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NOVA_DIST"
		optimize "On"

