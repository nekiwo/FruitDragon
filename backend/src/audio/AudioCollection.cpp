/**
 * @file AudioCollection.cpp
 * @author nekiwo
 * @brief Audio collection that represents a list of files and metadata
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "audio/AudioCollection.hpp"

#include "audio/RawAudio.hpp"
#include <filesystem>
#include <string>
#include <iostream>
#include <regex>
#include <vector>
#include <unordered_set>

namespace fs = std::filesystem;


AudioCollection::AudioCollection() {
    
}

/**
 * @brief Indexes all tracks in specified path and converts them to lossless audio
 * 
 * @param folderPath Path to stored collection
 * @return Read error code
 */
int AudioCollection::indexCollection(fs::path folderPath) {
    if (!fs::is_directory(folderPath)) {
        return 2;
    }

    this->Name = folderPath.filename();

    for (const auto &entry : fs::directory_iterator(folderPath)) {
        fs::path trackPath = entry.path();
        std::string trackFileName = trackPath.filename();

        // Overwritten icon of the album
        if (trackPath.stem() == "icon" && this->Name != "Singles" && supportedIconExtensions.contains(trackPath.extension())) {
            this->CoverFilePath = trackPath;
            continue;
        }

        // Check if it's an audio file
        if (supportedTrackExtensions.contains(trackPath.extension())) {
            std::string trackName = std::regex_replace((std::string)trackPath.stem(), std::regex("_"), " ");
            
            RawAudio track;
            track.Name = trackName;

            this->addTrack(track);
        }
    }

    return 0;
}

/**
 * @brief Adds a track to the list
 * 
 * @param track Track object
 */
void AudioCollection::addTrack(RawAudio &track) {
    this->tracks.push_back(&track);
}

/**
 * @brief Loads audio collection from JSON
 * 
 * @param configPath Path to config folder
 * @return Read error code
 */
int AudioCollection::indexFromJSON() {

}

/**
 * @brief Saves the indexed collection to JSON cache
 * 
 * @param configPath Path to config folder
 * @return Read error code
 */
int AudioCollection::saveToJSON() {

}

/**
 * @brief Returns number of tracks in the collection
 * 
 * @return Track count
 */
int AudioCollection::getTrackCount() {
    return tracks.size();
}