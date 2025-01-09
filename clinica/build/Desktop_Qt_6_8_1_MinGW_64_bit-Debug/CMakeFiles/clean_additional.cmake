# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\clinica_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\clinica_autogen.dir\\ParseCache.txt"
  "clinica_autogen"
  )
endif()
