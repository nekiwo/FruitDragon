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
#include "AudioCollection.hpp"

class FileTree {
    public:
        FileTree();
        AudioCollection Singles;
        std::vector<AudioCollection> Albums;
        std::vector<AudioCollection> Playlists;
        int loadFromFilePath(std::string filePath);
        
    private:
        int indexFilePath(std::string filePath);
};

#endif