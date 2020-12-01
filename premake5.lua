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
		--"%{prj.location}/Simulator/src/vendor/stb_image/**.cpp",
		--"%{prj.location}/Simulator/src/vendor/stb_image/**.h",
		"%{prj.location}/Simulator/res/shaders/**.*",
		"%{prj.location}/Simulator/res/textures/**.*",
		"%{prj.location}/Simulator/src/Solar/**.h",
		"%{prj.location}/Simulator/src/Solar/**.cpp",
		"%{prj.location}/Simulator/src/Graphics/**.h",
		"%{prj.location}/Simulator/src/Graphics/**.cpp"
	}

	excludes 
	{
		"%{prj.location}/Simulator/src/vendor/stb_image/**.cpp",
		"%{prj.location}/Simulator/src/vendor/stb_image/**.h",
		"%{prj.location}/Dependencies/imgui/include/main.cpp"
	}

	includedirs
	{
		"%{prj.location}",
		"%{prj.location}/Dependencies/GLEW/include",
		"%{prj.location}/Dependencies/GLFW/include",
		"%{prj.location}/Simulator/src",
		--"%{prj.location}/Simulator/src/vendor/stb_image",
		"%{prj.location}/Simulator/src/Solar",
		"%{prj.location}/Dependencies/SFML/include",
		"%{prj.location}/Dependencies/glm/include",
		"%{prj.location}/Simulator/src/Graphics",
		"%{prj.location}/Dependencies/imgui/include"
	}
	
	links 
	{	-- OPENGL libs
		"glfw3.lib","opengl32.lib","User32.lib","Gdi32.lib","Shell32.lib","glew32s.lib",
		-- SFML libs
		"openal32.lib","sfml-audio-s-d.lib","ogg.lib","vorbis.lib","vorbisfile.lib","vorbisenc.lib","flac.lib","sfml-main-d.lib",
		"ws2_32.lib","gdi32.lib","winmm.lib","freetype.lib","sfml-network-s-d.lib",
		"sfml-graphics-s-d.lib","sfml-window-s-d.lib","sfml-system-s-d.lib","kernel32.lib","user32.lib",
		"gdi32.lib","winspool.lib","comdlg32.lib","advapi32.lib","shell32.lib","ole32.lib","oleaut32.lib",
		"uuid.lib","odbc32.lib","odbccp32.lib"

	}
	
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "Off"
		
		defines 
		{ 
			"GLEW_STATIC","WIN32","SFML_STATIC"
		}

		libdirs
		{
			"%{prj.location}/Dependencies/GLFW/lib-vc2019", 
			"%{prj.location}/Dependencies/GLEW/lib/Release/Win32",
			"%{prj.location}/Dependencies/SFML/lib",
			"%{prj.location}/Dependencies/SFML/bin"
		}

				
	filter "configurations:Debug"
      	defines { "DEBUG" }
      	symbols "On"

   	filter "configurations:Release"
      	defines { "NDEBUG" }
      	optimize "On"

	configuration "windows"
   	postbuildcommands { "copy %{prj.location}Dependencies\\SFML\\bin\\openal32.dll %{prj.location}bin\\" .. outputdir .. "\\%{prj.name}" }
