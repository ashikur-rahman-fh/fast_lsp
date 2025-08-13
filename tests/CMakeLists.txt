add_executable(
  fast_lsp_test 
  test_main.cpp
  ws_watcher_tests.cpp
)

target_link_libraries(
  fast_lsp_test
  PRIVATE 
  GTest::gtest 
  GTest::gtest_main
  
  # include other external libraries
  spdlog::spdlog_header_only
  nlohmann_json::nlohmann_json
  # include all the libraries
  logging
  utils
  indexer
)

enable_testing()

target_include_directories(
  fast_lsp_test
  PUBLIC
  ${CMAKE_SOURCE_DIR}/include 
)
