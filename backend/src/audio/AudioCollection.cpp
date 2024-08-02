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
#include "utils/Config.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <taglib/tstring.h>
#include <thread>
#include <vector>
#include <unordered_set>
#include <taglib/fileref.h> 

namespace fs = std::filesystem;


AudioCollection::AudioCollection() {
    
}

/**
 * @brief Executes CLI
 * 
 * @param programName 
 */
void executeProgram(std::string programName) {
    system(programName.c_str());
}

/**
 * @brief Converts any audio file to WAV using FFmpeg command
 * 
 * @param filePath Path to file
 * @return Error code
 */
int convertAudioToWAV(fs::path originalFilePath, fs::path newFilePath) {
    std::thread worker (executeProgram, "ffmpeg -i " + (std::string)originalFilePath + " -acodec pcm_s24le -ar 44100 " + (std::string)newFilePath);
    worker.join();
    return 0;
}

/**
 * @brief Indexes all tracks in specified path and converts them to lossless audio
 * 
 * @param folderPath Path to stored collection
 * @return Read error code
 */
int AudioCollection::indexCollection(fs::path &collectionPath, AudioCacheTable &cache, Config &config) {
    if (!fs::is_directory(collectionPath)) {
        return 2;
    }

    this->Name = collectionPath.filename();

    // For each track
    int trackIterator = 0;
    for (const auto &entry : fs::directory_iterator(collectionPath)) {
        const fs::path trackPath = entry.path();
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

            // Check if folder contains temp file
            if (fs::exists(collectionPath / ".cache")) {
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
                TagLib::AudioProperties* properties = audioFile.audioProperties();
                track.Name = audioTag->title().to8Bit(true);
                track.Artists.push_back(audioTag->artist().to8Bit(true));
                track.LengthInSeconds = properties->lengthInSeconds();
                track.TrackNumber = audioTag->track();
                track.Year = audioTag->year();

                // Generate a standalone PNG icon file
                const fs::path iconPath = trackPath.parent_path() / "icon.jpg" ;
                TagLib::StringList names = audioFile.complexPropertyKeys();
                for(const auto &name : names) {
                    const auto& properties = audioFile.complexProperties(name);
                    for(const auto &property : properties) {
                        for(const auto &[key, value] : property) {
                            if(value.type() == TagLib::Variant::ByteVector) {
                                std::ofstream picture;
                                picture.open((std::string)iconPath, std::ios_base::out | std::ios_base::binary);
                                picture << value.value<TagLib::ByteVector>();
                                picture.close();
                            }
                        }
                    }
                }

                // Create audio cache as signed 24-bit little-endian PCM audio in a WAV container
                if (!fs::exists(config.MediaFolderPath / "Cache") || !fs::exists(config.MediaFolderPath / "Cache" / this->Name)) {
                    // TODO: error handling (and every other time `std::filesystem` is used)
                    std::filesystem::create_directory(config.MediaFolderPath / "Cache");
                    std::filesystem::create_directory(config.MediaFolderPath / "Cache" / this->Name);
                }
                const fs::path cachedTrackPath = config.MediaFolderPath / "Cache" / this->Name / ("track" + std::to_string(trackIterator) + ".wav");
                std::cout << (std::string)trackPath << std::endl;
                std::cout << (std::string)cachedTrackPath << std::endl;
                int error = convertAudioToWAV(trackPath, cachedTrackPath);
                if (error != 0) {
                    return error;
                }

                // Put newly generated files into JSON
                // TODO: fix fatal error
                cache.TrackCacheMap[trackPath] = cachedTrackPath;
                cache.IconCacheMap[collectionPath] = iconPath;

                // Create a temp file to signifify the collection has been cached
                std::ofstream { ".cached" };

                this->addTrack(track);
            }
        }

        trackIterator++;
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