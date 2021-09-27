workspace "levitate3D"
    architecture "x64"

    configurations
    {
        "Debug"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}.%{cfg.architecture}"

IncludeDirectories = {}
IncludeDirectories["spdlog"] = "gueepo2D/thirdparty/spdlog-1.9.2/include"
LibDir = {}

project "levitate3D"
    location "levitate3D/levitate3D"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    warnings "Extra"

    targetdir("%{prj.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{prj.location}/binobj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/thirdparty/glad/src/glad.c",
        "%{prj.location}/thirdparty/dearimgui/**.cpp",
    }

    includedirs
    {
        "%{prj.location}/src",
        "%{prj.location}/thirdparty/glad/include",
        "%{prj.location}/thirdparty/glfw-3.3.4.bin.WIN64/include",
        "%{prj.location}/thirdparty/glm",
        "%{prj.location}/thirdparty/dearimgui",
    }

    libdirs
    {
        "%{prj.location}/thirdparty/glfw-3.3.4.bin.WIN64/lib-vc2019",
    }

    filter "system:windows"
        links
        {
            "glfw3.lib",
        }