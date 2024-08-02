#include <gtest/gtest.h>
#include <filesystem>
#include <string>

#include "audio/FileTree.hpp"
#include "utils/Config.hpp"

namespace fs = std::filesystem;


TEST(FileTreeTest, IOTest) {
    // Config test needs to pass for this one
    Config config;
    std::string configFolderPath = fs::current_path().parent_path().parent_path() / "tests/config/";
    std::cout << (std::string)configFolderPath << std::endl;
    config.readFromFolder(configFolderPath);

    FileTree tree;
    int error = tree.loadFromPath((std::string)config.MediaFolderPath, *config.Cache, config);
    ASSERT_EQ(error, 0);

    EXPECT_EQ(tree.Albums.size(), 2); // Two albums
    EXPECT_EQ(tree.Singles.getTrackCount(), 2); // Two singles
}