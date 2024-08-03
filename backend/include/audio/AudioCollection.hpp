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

#include "audio/RawAudio.hpp"
#include "utils/Config.hpp"
#include <filesystem>
#include <string>
#include <unordered_set>
#include <vector>

namespace fs = std::filesystem;


class AudioCollection {
    public:
        AudioCollection();
        std::string Name;
        std::string ID;
        fs::path CoverFilePath;
        int indexCollection(fs::path &collectionPath, Config &config);
        void addTrack(RawAudio &track);
        RawAudio& getTrack(unsigned int index);
        int getTrackCount();

    private:
        // Commonly supported web image file formats
        std::unordered_set<std::string> supportedIconExtensions = {".apng", ".png", ".avif", ".gif", ".jpg", ".jpeg", ".jfif", ".pjpeg", ".pjp", ".webp"};
        // Commonly supported web sound file formats
        std::unordered_set<std::string> supportedTrackExtensions = {".aiff", ".flac", ".m4a", ".mp3", ".ogg", ".wav", ".webm"};
        std::vector<RawAudio*> tracks;
};

#endif