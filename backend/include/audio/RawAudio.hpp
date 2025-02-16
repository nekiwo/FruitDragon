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
#include <fstream>
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
        std::string AudioFilePath;
        std::string CoverFilePath;
        int openFile();
        int closeFile();
        std::vector<char> getBuffer(uint32_t chunkSize);
        std::vector<char> getBufferAt(uint32_t startIndex, uint32_t chunkSize);
    private:
        bool isOpened = false;
        std::ifstream inAudio;
        uint32_t dataSize;
};

#endif