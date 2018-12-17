solution "Decoda"
    platforms { "x86", "x64" }
    configurations { "Debug", "Release" }
    location "build"
    symbols "On"
    objdir "build/obj/%{prj.name}/%{cfg.buildcfg}%{cfg.platform}"
    targetdir "bin/%{cfg.buildcfg}"
    characterset "MBCS" 
    flags { }
    
    defines { "_CRT_SECURE_NO_WARNINGS", "WIN32" }
    
    vpaths { 
        ["Header Files"] = { "**.h" },
        ["Source Files"] = { "**.cpp" },
        ["Resource Files"] = { "**.rc" },
    }
    filter "Release"
        defines { "NDEBUG" }
        optimize "On"

    filter "Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "platforms:x64"
        architecture "x86_64"
        vectorextensions "SSE2"
        defines { "DECODA_X64=1" }
        
    filter "platforms:x86"
        defines { "DECODA_X64=0" }
    filter{}
    
project "Frontend"
    kind "WindowedApp"
    platforms { "x86" }
    targetname "Decoda"
    entrypoint "WinMainCRTStartup"
    location "build"
    language "C++"
    dependson { "LuaInject", "tinyxml" }
    flags { "MultiProcessorCompile" }
    linkoptions { "/ignore:4099" } 
    files {
        "src/Frontend/*.h",
        "src/Frontend/*.cpp",
        "src/Frontend/*.rc",
    }        
    includedirs {
        "src/Shared",
        "libs/wxWidgets/include",
        "libs/wxScintilla/include",
    }
    libdirs {
        "libs/wxWidgets/lib/vc_lib",
        "libs/wxScintilla/lib",
        "build/libs/%{cfg.buildcfg}%{cfg.platform}",
    }
    links {
        "comctl32",
        "rpcrt4",
        "imagehlp",
        "Shared%{cfg.platform}",
        "tinyxml"
    }

    filter "Debug"
        includedirs { 
          "libs/wxWidgets/lib/vc_lib/mswd" 
        }
        links {
            "wxbase28d",
            "wxmsw28d_core",
            "wxmsw28d_aui",
            "wxscintillad",
            "wxbase28d_xml",
            "wxexpatd",
            "wxmsw28d_adv",
            "wxmsw28d_qa",
            "wxzlibd",
            "wxmsw28d_richtext",
            "wxmsw28d_html",
            "wxpngd",
        }

    filter "Release"
        includedirs { 
          "libs/wxWidgets/lib/vc_lib/msw" 
        }
        links {
            "wxbase28",
            "wxmsw28_core",
            "wxmsw28_aui",
            "wxscintilla",
            "wxbase28_xml",
            "wxexpat",
            "wxmsw28_adv",
            "wxmsw28_qa",
            "wxzlib",
            "wxmsw28_richtext",
            "wxmsw28_html",
            "wxpng",
        }        
        
project "LuaInject"
    kind "SharedLib"
    targetname "LuaInject%{cfg.platform}"
    platforms { "x86", "x64" }
    location "build"
    dependson { "tinyxml" }
    language "C++"
    defines { "TIXML_USE_STL" }
    linkoptions { "/export:DetourFinishHelperProcess,@1,NONAME" }
    files {
        "src/LuaInject/*.h",
        "src/LuaInject/*.cpp",
    }        
    includedirs {
        "src/Shared",
        "libs/LuaPlus/include",
        "libs/tinyxml/include",
        "libs/dbghlp/include",
        "libs/Detours/include",
    }
    libdirs {
        "libs/dbghlp/lib",
        "build/libs/%{cfg.buildcfg}%{cfg.platform}",
        "libs/Detours/lib",
    }
    links {
        "Shared",
        "psapi",
        "detours%{cfg.platform}",
    }

    filter "Debug"
        links { "tinyxmld%{cfg.platform}" }

    filter "Release"        
        links { "tinyxml%{cfg.platform}" }

    filter "platforms:x86"
        targetname "LuaInject32"
    filter "platforms:x64"
        targetname "LuaInject64"

project "Shared"
    kind "StaticLib"
    platforms { "x86", "x64" }
    targetdir "build/libs/%{cfg.buildcfg}%{cfg.platform}"
    targetname "Shared%{cfg.platform}"
    location "build"
    language "C++"
    files {
        "src/Shared/*.h",
        "src/Shared/*.cpp",
    }

project "tinyxml"
    kind "StaticLib"
    platforms { "x86", "x64" }
    targetdir "build/libs/%{cfg.buildcfg}%{cfg.platform}"
    location "build"
    language "C++"
    defines {"_LIB", "TIXML_USE_STL" }
    files {
        "libs/tinyxml/src/tinystr.cpp",
        "libs/tinyxml/src/tinyxml.cpp",
        "libs/tinyxml/src/tinyxmlparser.cpp",
        "libs/tinyxml/src/tinyxmlerror.cpp",
    }
    filter "Debug"
        targetname "tinyxmld%{cfg.platform}"

    filter "Release"
        targetname "tinyxml%{cfg.platform}"