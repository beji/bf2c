cmake_minimum_required(VERSION 3.16)

project(virtcputhing
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address -fsanitize=undefined -Wall")
string(APPEND CMAKE_LINKER_FLAGS_DEBUG " -fsanitize=address -fsanitize=undefined -Wall")

string(APPEND CMAKE_CXX_FLAGS_RELEASE " -Wall -pipe")
string(APPEND CMAKE_LINKER_FLAGS_RELEASE "-Wall")

add_executable(bf2c "${CMAKE_CURRENT_SOURCE_DIR}/src/bf2c.cpp")

if (CMAKE_BUILD_TYPE STREQUAL "Release")

  include(CheckIPOSupported)

  # Optional IPO. Do not use IPO if it's not supported by compiler.
  check_ipo_supported(RESULT ltoSupport OUTPUT output)
  if(ltoSupport)
    set_property(TARGET bf2c PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)    
  else()
    message(WARNING "IPO is not supported: ${output}")
  endif()

endif()
