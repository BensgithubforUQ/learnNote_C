# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\helloWorld_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\helloWorld_autogen.dir\\ParseCache.txt"
  "helloWorld_autogen"
  )
endif()
