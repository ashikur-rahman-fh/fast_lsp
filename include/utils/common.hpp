#include <string>
#include <vector>

namespace cmn {

constexpr std::string FAST_LSP_DIR = "fast_lsp";
constexpr std::string FAST_LSP_LOG_FILE = "fast_lsp.log";

const std::vector<std::string> C_FILE_EXTS = { ".c", ".h" }; 
const std::vector<std::string> CPP_FILE_EXTS = {
  ".cc", ".cpp", ".cxx", ".hpp", ".hxx"
}; 

std::string GetHomeDirectory();

bool IsCFile(const std::string& ext);

bool IsCppFile(const std::string& ext);

void InitFastLsp();

} // namespace cmn ends
