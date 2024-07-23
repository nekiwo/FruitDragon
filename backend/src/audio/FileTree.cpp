/**
 * @file FileTree.hpp
 * @author nekiwo
 * @brief Class to recursively scan specified folder for a catalogue tree
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <filesystem>
#include <string>

#include "audio/FileTree.hpp"
#include "audio/AudioCollection.hpp"

namespace fs = std::filesystem;


FileTree::FileTree() {

}

/**
 * @brief Loads tree into class object from specified folder path
 * 
 * @param filePath Path to stored media
 * @return Read error code
 */
int FileTree::loadFromPath(std::string folderPath) {
    if (!fs::is_directory(folderPath)) {
        return 2;
    }

    for (const auto &entry : fs::directory_iterator(folderPath)) {
        fs::path path = entry.path();
        std::string dirName = path.filename();

        if (dirName == "Singles") {
            int error = this->Singles.indexCollection(path);
            if (error != 0) return error;
        } else if (dirName == "Albums") {
            for (const auto &albumEntry : fs::directory_iterator(folderPath)) {
                fs::path albumDir = albumEntry.path();
                AudioCollection album;
                int error = album.indexCollection(albumDir);
                if (error != 0) return error;
                this->Albums.push_back(album);
            }
        }
    }

    return 0;
}