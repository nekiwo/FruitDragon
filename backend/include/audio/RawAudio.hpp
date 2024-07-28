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

#include <string>
#include <vector>

class RawAudio {
    public:
        RawAudio();
        std::string Name;
        std::vector<std::string> Artists;
        unsigned int TrackNumber;
        unsigned int Year;
        std::string AudioFilePath;
        std::string CoverFilePath;
        int readFromFile(std::string filePath);
        int loadFromFile(std::string filePath);
        char* getBuffer(int startIndex, int endIndex);
};

#endif