#include <cstddef>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

namespace indexer {

enum FileState {
  CLEAN, /// already processed
  DIRTY /// no processed 
};

class File {
public:
  File(const std::string& path);

  /// get state of the file
  FileState GetState() const;
  
  /// set state of the file
  void SetState(const FileState& state);

  /// get file path
  std::string GetPath() const;

  /// set file path
  void SetPath(const std::string& path);
  
  /// make file state clean
  void MakeClean();
  
  /// make file state dirty
  void MakeDirty();

  /// comparison
  bool operator == (const File& other) const;
  bool operator != (const File& other) const;

private:
  std::string path_m;
  FileState state_m;
};


struct FileHash {
  std::size_t operator() (const File& file) const noexcept;
};

typedef std::unordered_set<File, FileHash> FileSetType;

class Workspace {
public:
  Workspace(const std::string& root);
  
  /// look for all the c/c++ files in the workspace
  /// and store in the the files vector
  void Crawl();
  
  /// returns the the files vector
  std::vector<File> GetFiles();
  
  /// returns the root of the workspace
  std::string GetRoot() const;
  
  /// add a file to the workspace
  void AddFile(const File& file);
  
  /// remove a file from the workspace
  void RemoveFile(const File& file);

  /// modify file with a new file
  void ModifyFile(const File& prev, const File& next);

private:
  std::string root_m;
  FileSetType files_m;
  std::queue<FileSetType::iterator> indexQueue_m;
};

} // namespace indexer ends
