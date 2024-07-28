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

#include "audio/AudioCacheTable.hpp"
#include "audio/RawAudio.hpp"
#include <filesystem>
#include <string>
#include <regex>
#include <taglib/tstring.h>
#include <vector>
#include <unordered_set>
#include <taglib/fileref.h> 

namespace fs = std::filesystem;


AudioCollection::AudioCollection() {
    
}

/**
 * @brief Indexes all tracks in specified path and converts them to lossless audio
 * 
 * @param folderPath Path to stored collection
 * @return Read error code
 */
int AudioCollection::indexCollection(fs::path &collectionPath, AudioCacheTable &cache) {
    if (!fs::is_directory(collectionPath)) {
        return 2;
    }

    this->Name = collectionPath.filename();

    for (const auto &entry : fs::directory_iterator(collectionPath)) {
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
            
            if (cache.Completed) {
                track.AudioFilePath = cache.TrackCacheMap[trackPath];
                track.CoverFilePath = cache.IconCacheMap[collectionPath];

                // track.Name = 
                // track.Artists.push_back();
                // track.TrackNumber = 
                // track.Year = 
            } else {
                // Load metadata from original file
                TagLib::FileRef audioFile(((std::string)trackPath).c_str());
                TagLib::Tag* audioTag = audioFile.tag();
                track.Name = audioTag->title().to8Bit(true);
                track.Artists.push_back(audioTag->artist().to8Bit(true));
                track.TrackNumber = audioTag->track();
                track.Year = audioTag->year();

                // TODO: Generate a standalone PNG icon file


                // TODO: Cache the whole thing into JSON

            }

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