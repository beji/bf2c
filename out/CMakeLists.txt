cmake_minimum_required(VERSION 3.16)

project(virtcputhing
  LANGUAGES C
)

set(CMAKE_CXX_STANDARD 11)

string(APPEND CMAKE_C_FLAGS_DEBUG " -fsanitize=address -fsanitize=undefined -Wall")
string(APPEND CMAKE_LINKER_FLAGS_DEBUG " -fsanitize=address -fsanitize=undefined -Wall")

string(APPEND CMAKE_C_FLAGS_RELEASE " -Wall -pipe")
string(APPEND CMAKE_LINKER_FLAGS_RELEASE "-Wall")

add_executable(bf "${CMAKE_CURRENT_SOURCE_DIR}/bf.c")

if (CMAKE_BUILD_TYPE STREQUAL "Release")

  include(CheckIPOSupported)

  # Optional IPO. Do not use IPO if it's not supported by compiler.
  check_ipo_supported(RESULT ltoSupport OUTPUT output)
  if(ltoSupport)
    set_property(TARGET bf PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)    
  else()
    message(WARNING "IPO is not supported: ${output}")
  endif()

endif()
