#include <gtest/gtest.h>
#include <filesystem>
#include <ios>
#include <string>

#include "audio/FileTree.hpp"
#include "audio/RawAudio.hpp"
#include "utils/Config.hpp"

namespace fs = std::filesystem;


TEST(FileTreeTest, IOTest) {
    // fs::path configFolderPath = fs::current_path().parent_path() / "backend/tests/config/";
    fs::path configFolderPath = fs::current_path().parent_path().parent_path() / "tests/config/";

    // Remove previous cache
    fs::remove_all(configFolderPath / "../Cache");
    fs::remove(configFolderPath / "../Cache/Singles/.cached");
    for (const auto &entry : fs::directory_iterator(configFolderPath / "../music/Albums/")) {
        const fs::path albumPath = entry.path();
        fs::remove(albumPath / ".cached");
    }

    // Load config
    Config config;
    config.readFromFolder(configFolderPath);

    // Make cache
    FileTree tree;
    int error = tree.loadFromPath((std::string)config.MediaFolderPath, config);
    ASSERT_EQ(error, 0);

    // Read audio chunks
    RawAudio& track = tree.Singles.getTrack(0);
    track.openFile();
    std::vector<char> buffer = track.getBuffer(16);

    for (char i: buffer)
        std::cout << std::hex << i << ' ';
    std::cout << std::endl;

    EXPECT_EQ(tree.Albums.size(), 2); // Two albums
    EXPECT_EQ(tree.Singles.getTrackCount(), 2); // Two singles

    // TODO: Load from cache
    
}