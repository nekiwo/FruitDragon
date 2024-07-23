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

#include <filesystem>
#include <string>
#include <unordered_set>
#include <vector>
#include "audio/RawAudio.hpp"

namespace fs = std::filesystem;


class AudioCollection {
    public:
        AudioCollection();
        std::string Name;
        std::string ID;
        std::string CoverFilePath;
        int indexCollection(fs::path folderPath);
        void addTrack(RawAudio &track);
        int getTrackCount();

    private:
        std::unordered_set<std::string> supportedIconExtensions;
        std::vector<RawAudio> tracks;
        int indexFromJSON();
        int saveToJSON();
};

#endif