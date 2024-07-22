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

#include "audio/AudioCollection.hpp"


AudioCollection::AudioCollection() {

}

/**
 * @brief Indexes all tracks in specified path and converts them to lossless audio
 * 
 * @param folderPath Path to stored collection
 * @return Read error code
 */
int AudioCollection::indexCollection(std::string folderPath) {

}

/**
 * @brief Adds a track to the list
 * 
 * @param track Track object
 */
void AudioCollection::addTrack(RawAudio &track) {
    this->tracks.push_back(track);
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