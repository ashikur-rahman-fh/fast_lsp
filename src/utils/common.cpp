#include <algorithm>
#include <filesystem>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "utils/common.hpp"
namespace cmn {
  
std::string GetHomeDirectory() {
  std::string home = std::getenv("HOME");

  if (!home.empty()) {
    return home;
  }

  home = std::getenv("USERPROFILE");
  if (!home.empty()) {
    return home;
  }

  return {};
}

bool IsCFile(const std::string& ext) {
  return std::find(C_FILE_EXTS.begin(), C_FILE_EXTS.end(), ext) != 
    C_FILE_EXTS.end();
}

bool IsCppFile(const std::string& ext) {
  return std::find(CPP_FILE_EXTS.begin(), CPP_FILE_EXTS.end(), ext) !=
    CPP_FILE_EXTS.end();
}

void InitFastLsp() {
  const std::string home = GetHomeDirectory();
  if (home.empty()) {
    std::cerr << "Can not find home directory. Initialization failed." << std::endl;
    std::exit(EXIT_FAILURE);
  }
  const std::filesystem::path homeDir = home;
  const std::filesystem::path fastLspDir = FAST_LSP_DIR;

  std::filesystem::create_directory(homeDir / fastLspDir);
}

} // namespace cmn ends
