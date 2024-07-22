#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "audio/FileTree.hpp"
#include "utils/Config.hpp"


TEST(FileTreeTest, IOTest) {
    // Config test needs to pass for this one
    Config config;
    std::string homePath = getenv("HOME");
    std::string configPath = homePath.append("/Music/FruitDragon/config.json");
    config.readFromFile(configPath);

    FileTree tree;
    int error = tree.loadFromPath(config.MediaFolderPath);

    EXPECT_EQ(error, 0);
}