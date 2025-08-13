#include "gtest/gtest.h"

#include "indexer/ws_watcher.hpp"

class FileTest : public testing::Test {
protected:
  FileTest() {}

  indexer::File *file = new indexer::File("/some/path/to/file.cpp");
};

TEST_F(FileTest, FileStateIsDirtyInitially) {
  ASSERT_EQ(file -> GetState(), indexer::FileState::DIRTY);
}

TEST_F(FileTest, GetPathMustReturnProvidedPathDuringConstruction) {
  ASSERT_EQ(file -> GetPath(), "/some/path/to/file.cpp");
}

TEST_F(FileTest, SetStateMustSetTheProvidedNewState) {
  file -> SetState(indexer::FileState::CLEAN);
  ASSERT_EQ(file -> GetState(), indexer::FileState::CLEAN);

  file -> SetState(indexer::FileState::DIRTY);
  ASSERT_EQ(file -> GetState(), indexer::FileState::DIRTY);

  file -> SetState(indexer::FileState::CLEAN);
  ASSERT_EQ(file -> GetState(), indexer::FileState::CLEAN);

  file -> SetState(indexer::FileState::DIRTY);
  ASSERT_EQ(file -> GetState(), indexer::FileState::DIRTY);
}

TEST_F(FileTest, SetPathMustSetTheNewProvidedPath) {
  file -> SetPath("/some/new/path.cpp");
  ASSERT_EQ(file -> GetPath(), "/some/new/path.cpp");
}

TEST_F(FileTest, MakeDirtryMustMakeTheFileStateDirty) {
  file -> MakeDirty();
  ASSERT_EQ(file -> GetState(), indexer::FileState::DIRTY);
}

TEST_F(FileTest, MakeCleanMustMakeTheFileStateClean) {
  file -> MakeClean();
  ASSERT_EQ(file -> GetState(), indexer::FileState::CLEAN);
}


TEST_F(FileTest, FileMustBeEqualWhenTheFilePathIsSame) {
  indexer::File *same = new indexer::File("/some/path/to/file.cpp");
  ASSERT_EQ(*file, *same);
  ASSERT_TRUE(*file == *same);
}

TEST_F(FileTest, FileMustBeDifferentWhenTheFilePathIsNotSame) {
  indexer::File *different = new indexer::File("/some/path/to/another/file.cpp");
  ASSERT_NE(*file, *different);
  ASSERT_TRUE(*file != *different);
}
