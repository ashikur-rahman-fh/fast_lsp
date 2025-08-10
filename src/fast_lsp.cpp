#include "utils/common.hpp"
#include "indexer/ws_watcher.hpp"
#include "logging/logger.hpp"

int main() {
  cmn::InitFastLsp();
  logging::init(); // no logs before this line

  return 0;
}
