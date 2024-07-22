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
#include "audio/RawAudio.hpp"

class AudioCollection {
    public:
        AudioCollection();
        std::string Name;
        std::string ID;
        std::string CoverFilePath;
        int indexCollection(std::string folderPath);
        void addTrack(RawAudio &track);

    private:
        std::vector<RawAudio> tracks;
        int indexFromJSON();
        int saveToJSON();
};

#endif