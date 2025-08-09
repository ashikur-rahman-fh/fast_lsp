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

} // namespace cmn ends
