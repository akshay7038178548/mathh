   project "mathh"
      location "_build"
      kind "StaticLib"
      language "C++"
      includedirs { "." }
      files { "src/**.h", "src/**.cpp" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

