workspace "DawnStar"
	architecture "x64"

	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirMap = {}
IncludeDirMap["GLFW"] = "DawnStar/dependencies/glfw-3.3.6/include"
IncludeDirMap["Glad"] = "DawnStar/dependencies/glad/include"
IncludeDir["glm"] = "DawnStar/dependencies/glm"

group "dependencies"
	include "DawnStar/dependencies/glfw-3.3.6"
	include "DawnStar/dependencies/glad"
group ""

project "DawnStar"
	location "DawnStar"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-temp/" .. outputdir .. "/%{prj.name}")

	pchheader "dspch.h"
	pchsource "%{prj.name}/src/dspch.cpp"

	defines{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{IncludeDirMap.GLFW}",
		"%{IncludeDirMap.Glad}",
		"%{IncludeDir.glm}",
	}

	links{
		"opengl32.lib",
		"GLFW",
		"Glad"
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		runtime "Release"
		optimize "On"

	filter "system:windows"
		systemversion "latest"

		defines{
			"DS_PLATFORM_WINDOWS"
		}

		-- 添加命令行：将生成的库复制到测试目录下
		postbuildcommands{
			("{COPYDIR} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-temp/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"DawnStar/src",

	}

	links{
		"DawnStar"
	}

	filter "system:windows"
		systemversion "latest"

		defines{
			"DS_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "DS_Release"
		runtime "Release"
		optimize "on"
