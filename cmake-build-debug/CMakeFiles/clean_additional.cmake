# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BaseOrrery_autogen"
  "CMakeFiles/BaseOrrery_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/BaseOrrery_autogen.dir/ParseCache.txt"
  )
endif()
