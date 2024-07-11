/**
 * @file AudioCollection.hpp
 * @author nekiwo
 * @brief Audio collection that represents a list of files and metadata
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef AUDIO_COLLECTION
#define AUDIO_COLLECTION

#include <string>
#include <vector>
#include "RawAudio.hpp"

class AudioCollection {
    public:
        AudioCollection();
        std::string Name;
        std::string ID;
        std::string CoverFilePath;
        std::vector<RawAudio> Tracks;
        int indexCollection(std::string folderPath, std::string configPath);

    private:
        int indexFromJSON(std::string configPath);
        int saveToJSON(std::string configPath);
};

#endif