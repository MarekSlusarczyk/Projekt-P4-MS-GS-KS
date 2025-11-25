# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\logowanie_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\logowanie_autogen.dir\\ParseCache.txt"
  "logowanie_autogen"
  )
endif()
