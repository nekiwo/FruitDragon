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

#ifndef FILE_TREE
#define FILE_TREE

#include <string>
#include <vector>
#include "audio/AudioCollection.hpp"

class FileTree {
    public:
        FileTree();
        AudioCollection Singles;
        std::vector<AudioCollection> Albums;
        std::vector<AudioCollection> Playlists;
        int loadFromPath(std::string folderPath);
};

#endif