/**
 * @file RawAudio.hpp
 * @author nekiwo
 * @brief Common audio format ready to be served over a stream
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef RAW_AUDIO
#define RAW_AUDIO

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;


class RawAudio {
    public:
        RawAudio();
        std::string Name;
        std::vector<std::string> Artists;
        unsigned int LengthInSeconds;
        unsigned int TrackNumber;
        unsigned int Year;
        fs::path AudioFilePath;
        fs::path CoverFilePath;
        int readFromFile(std::string filePath);
        int loadFromFile(std::string filePath);
        char* getBuffer(int startIndex, int endIndex);
};

#endif