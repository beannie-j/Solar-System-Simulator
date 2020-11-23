workspace "SolarSystemSimulator"
	architecture "x86"
	targetdir "build"
	
	configurations 
	{ 
		"Debug", 
		"Release"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Dependencies/GLFW/include"
IncludeDir["GLEW"] = "Dependencies/GLEW/include"

project "SolarSystemSimulator"
	location "."
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


	files 
	{ 
		"%{prj.location}/Simulator/src/**.h", 
		"%{prj.location}/Simulator/src/**.c", 
		"%{prj.location}/Simulator/src/**.hpp", 
		"%{prj.location}/Simulator/src/**.cpp",
		"%{prj.location}/Simulator/src/vendor/stb_image/**.cpp",
		"%{prj.location}/Simulator/src/vendor/stb_image/**.h",
		"%{prj.location}/Simulator/res/shaders/**.*",
		"%{prj.location}/Simulator/res/textures/**.*"
	}

	includedirs
	{
		"%{prj.location}",
		"%{prj.location}/Dependencies/GLEW/include",
		"%{prj.location}/Dependencies/GLFW/include",
		"%{prj.location}/Simulator/src",
		"%{prj.location}/Simulator/src/vendor/stb_image"
	}
	
	links 
	{ 
		"glfw3.lib","opengl32.lib","User32.lib","Gdi32.lib","Shell32.lib","glew32s.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "Off"
		
		defines 
		{ 
			"GLEW_STATIC","WIN32"
		}

		libdirs
		{
			"%{prj.location}/Dependencies/GLFW/lib-vc2019", "%{prj.location}/Dependencies/GLEW/lib/Release/Win32"
		}

				
	filter "configurations:Debug"
      	defines { "DEBUG" }
      	symbols "On"

   	filter "configurations:Release"
      	defines { "NDEBUG" }
      	optimize "On"

