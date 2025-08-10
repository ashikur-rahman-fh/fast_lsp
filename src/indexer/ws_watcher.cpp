#include <filesystem>
#include <string>
#include <vector>

#include "indexer/ws_watcher.hpp"
#include "logging/logger.hpp"
#include "utils/common.hpp"

namespace indexer {

File::File(const std::string& path) : path_m(path), state_m(FileState::DIRTY) {}

FileState File::GetState() const {
  return state_m;
}

void File::SetState(const FileState& state) {
  this -> state_m = state;
}

std::string File::GetPath() const {
  return path_m;
}

void File::SetPath(const std::string& path) {
  this -> path_m = path;
}

void File::MakeClean() {
  state_m = FileState::CLEAN;
}

void File::MakeDirty() {
  state_m = FileState::DIRTY;
}

bool File::operator == (const File& other) const {
  return path_m == other.path_m;
}

bool File::operator != (const File& other) const {
  return path_m != other.path_m;
}

std::size_t FileHash::operator() (const File& file) const noexcept {
  return std::hash<std::string> {} (file.GetPath());
}


Workspace::Workspace(const std::string& root) : root_m(root) {}

void Workspace::Crawl() {
  LOG_DEBUG("Crawling workspace {}.", root_m);
  LOG_INFO("Workspace crawler has started.");

  namespace fs = std::filesystem;
  
  if (!fs::exists(root_m) || !fs::is_directory(root_m)) {
    LOG_ERR("Workspace root {} is not a valid directory.", root_m);
  }

  for (const auto& fs_file : fs::recursive_directory_iterator(root_m)) {
    if (fs::is_regular_file(fs_file.status())) {
      std::string extension = fs_file.path().extension().string();
      if (cmn::IsCFile(extension) || cmn::IsCppFile(extension)) {
        AddFile(fs_file.path().string());
      }
    }
  }
}

std::vector<File> Workspace::GetFiles() {
  return std::vector<File> (files_m.begin(), files_m.end());
}

std::string Workspace::GetRoot() const {
  return root_m;
}

void Workspace::AddFile(const File& file) {
  LOG_DEBUG("Adding {} to workspace.", file.GetPath());
  if (files_m.contains(file)) { 
    LOG_ERR("File {} is already in the workspace.", file.GetPath());
  }

  auto [it, inserted] = files_m.insert(file);
  if (inserted && it -> GetState() == FileState::DIRTY) {
    indexQueue_m.push(it);
    LOG_DEBUG("File {} is inserted to the index queue", it -> GetPath());
  }
}

void Workspace::RemoveFile(const File& file) {
  LOG_DEBUG("Removing {} from workspace.", file.GetPath());
  if (!files_m.contains(file)) {
    LOG_ERR("File {} is not found in the workspace.", file.GetPath());
  }

  files_m.erase(files_m.find(file));
}

void Workspace::ModifyFile(const File& prev, const File& next) {
  LOG_DEBUG("Updating {} with {}.", prev.GetPath(), next.GetPath());
  if (files_m.contains(prev)) {
    files_m.erase(files_m.find(prev));
  } else {
    LOG_ERR("File {} is not found in the workspace.", prev.GetPath());
  }

  auto [it, inserted] = files_m.insert(next);
  if (inserted && it -> GetState() == FileState::DIRTY) {
    indexQueue_m.push(it);
    LOG_DEBUG("File {} is inserted to the index queue", it -> GetPath());
  }
}

} // namespace indexer ends
