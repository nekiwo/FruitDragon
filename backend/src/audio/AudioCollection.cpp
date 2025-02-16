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
#include "utils/Config.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <regex>
#include <taglib/tstring.h>
#include <thread>
#include <unordered_map>
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
    std::string ffmpegCommand = "ffmpeg -y -i \"" + (std::string)originalFilePath + "\" -loglevel quiet -acodec pcm_s16le -ac 2 -ar 44100 \"" + (std::string)newFilePath + "\"";
    std::thread worker (executeProgram, ffmpegCommand);
    worker.join();
    return 0;
}

/**
 * @brief Indexes all tracks in specified path and converts them to lossless audio
 * 
 * @param folderPath Path to stored collection
 * @return Read error code
 */
int AudioCollection::indexCollection(fs::path &collectionPath, Config &config) {
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

            // Check if folder contains temp file
            if (fs::exists(collectionPath / ".cache")) {
                // track->AudioFilePath = config.TrackCacheMap[trackPath];
                // track->CoverFilePath = config.IconCacheMap[collectionPath];

                // track.Name = 
                // track.Artists.push_back();
                // track.TrackNumber = 
                // track.Year = 
            } else {
                // Load metadata from original file
                TagLib::FileRef audioFile(((std::string)trackPath).c_str());
                TagLib::Tag* audioTag = audioFile.tag();

                unsigned int trackNum = audioTag->track();
                if (tracks.contains(trackNum))
                {
                    trackNum = 0;
                    while (tracks.contains(trackNum)) {
                        trackNum++;
                    }
                }

                this->addTrack(trackNum);
                RawAudio* track = getTrack(trackNum);

                TagLib::AudioProperties* properties = audioFile.audioProperties();
                track->Name = audioTag->title().to8Bit(true);
                track->Artists.push_back(audioTag->artist().to8Bit(true));
                track->LengthInSeconds = properties->lengthInSeconds();
                track->TrackNumber = trackNum;
                track->Year = audioTag->year();

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

                // Create audio cache as signed 16-bit little-endian 44.1khz PCM forced stereo audio in a WAV container
                if (!fs::exists(config.MediaFolderPath / "Cache") || !fs::exists(config.MediaFolderPath / "Cache" / this->Name)) {
                    // TODO: error handling (and every other time `std::filesystem` is used)
                    std::filesystem::create_directory(config.MediaFolderPath / "Cache");
                    std::filesystem::create_directory(config.MediaFolderPath / "Cache" / this->Name);
                }
                const fs::path cachedTrackPath = config.MediaFolderPath / "Cache" / this->Name / ("track" + std::to_string(trackIterator) + ".wav");
                int error = convertAudioToWAV(trackPath, cachedTrackPath);
                if (error != 0) {
                    return error;
                }

                // Put newly generated files into JSON
                track->AudioFilePath = cachedTrackPath.string();
                track->CoverFilePath = iconPath.string();
                config.TrackCacheMap[trackPath.string()] = cachedTrackPath.string();
                config.IconCacheMap[collectionPath.string()] = iconPath.string();

                // Create a temp file to signifify the collection has been cached
                std::ofstream { trackPath.parent_path() / ".cached" };
            }
        }

        trackIterator++;
    }

    std::cout << tracks[0]->AudioFilePath << std::endl;

    return 0;
}

/**
 * @brief Adds a track to the list
 * 
 * @param track Track object
 */
void AudioCollection::addTrack(unsigned int index) {
    this->tracks.insert({index, new RawAudio()});
}

RawAudio* AudioCollection::getTrack(unsigned int index) {
    std::cout << tracks[index]->AudioFilePath << std::endl;
    return tracks.at(index);
}

/**
 * @brief Returns number of tracks in the collection
 * 
 * @return Track count
 */
int AudioCollection::getTrackCount() {
    return tracks.size();
}