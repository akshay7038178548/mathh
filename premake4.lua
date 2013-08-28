   project "mathh"
      location "_build"
      kind "StaticLib"
      language "C++"
      includedirs { ".", "./src/glm" }
      files { "src/**.h", "src/**.cpp" }
      excludes { "src/glm/test/**", "src/glm/glm/core/**.cpp" }
 
      configuration "Debug"
         defines { "DEBUG", "_CRT_SECURE_NO_WARNINGS" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

