solution "Decoda"
    configurations { "Debug", "Release" }
    location "build"
    symbols "On"
    objdir "build/obj/%{prj.name}/%{cfg.buildcfg}"
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

project "Frontend"
    kind "WindowedApp"
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
    }
    links {
        "comctl32",
        "rpcrt4",
        "imagehlp",
        "Shared",
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
    location "build"
    language "C++"
    defines { "TIXML_USE_STL" }
    files {
        "src/LuaInject/*.h",
        "src/LuaInject/*.cpp",
    }        
    includedirs {
        "src/Shared",
        "libs/LuaPlus/include",
        "libs/tinyxml/include",
        "libs/dbghlp/include",
    }
    libdirs {
        "libs/dbghlp/lib",
    }
    links {
        "Shared",
        "psapi"
    }

    filter "Debug"
        links { "tinyxmld" }

    filter "Release"        
        links { "tinyxml" }
        
project "Shared"
    kind "StaticLib"
    location "build"
    language "C++"
    files {
        "src/Shared/*.h",
        "src/Shared/*.cpp",
    }

project "tinyxml"
    kind "StaticLib"
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
        targetname "tinyxmld"
        targetdir "bin/debug"

    filter "Release"
        targetname "tinyxml"
        targetdir "bin/release"