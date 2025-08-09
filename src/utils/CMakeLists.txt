add_library(
  utils
  common.cpp
)

target_include_directories(
  utils
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include 
)

