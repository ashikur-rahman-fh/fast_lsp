add_library(
  indexer
  indexer.cpp
  ws_watcher.cpp
)

target_link_libraries(
  indexer
  logging
)

target_include_directories(
  indexer
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include 
)

