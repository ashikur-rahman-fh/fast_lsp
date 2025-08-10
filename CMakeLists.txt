cmake_minimum_required(VERSION 3.0)

project(FastLsp VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/spdlog)
add_subdirectory(src/logging)
add_subdirectory(src/utils)
add_subdirectory(src/indexer)

add_executable(
  fast_lsp
  src/fast_lsp.cpp
)

target_link_libraries(
  fast_lsp
  PRIVATE
  logging
  utils
  indexer
)


target_compile_options(
  fast_lsp 
  PRIVATE
  -Wall -Wextra -Wpedantic -fdiagnostics-color=always -fdiagnostics-show-option
)
