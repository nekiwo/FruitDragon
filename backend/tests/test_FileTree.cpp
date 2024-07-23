#include <gtest/gtest.h>
#include <iostream>
#include <filesystem>
#include <string>

#include "audio/FileTree.hpp"
#include "utils/Config.hpp"

namespace fs = std::filesystem;


TEST(FileTreeTest, IOTest) {
    // Config test needs to pass for this one
    Config config;
    std::string configPath = fs::current_path().parent_path() / "tests/config/config.json";
    config.readFromFile(configPath);

    FileTree tree;
    int error = tree.loadFromPath(config.MediaFolderPath);
    ASSERT_EQ(error, 0);

    EXPECT_EQ(tree.Albums.size(), 2); // Two albums
    EXPECT_EQ(tree.Singles.getTrackCount(), 2); // Two singles
}