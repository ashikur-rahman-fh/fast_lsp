add_library(
  indexer
  indexer.cpp
  ws_watcher.cpp
  lexer.cpp
)

target_link_libraries(
  indexer
  logging
  utils
)

target_include_directories(
  indexer
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include 
)

