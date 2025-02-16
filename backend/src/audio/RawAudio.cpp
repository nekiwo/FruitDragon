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

#include "audio/RawAudio.hpp"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;


RawAudio::RawAudio() {

}

/**
 * @brief Opens file before reading buffers
 * 
 * @return Error code
 */
int RawAudio::openFile() {
    if (isOpened) {
        return 0;
    }
    inAudio.open(this->AudioFilePath);
    inAudio.ignore(16);
    uint32_t subchunk1Size;
    inAudio.read(reinterpret_cast<char*>(&subchunk1Size), sizeof(subchunk1Size));
    inAudio.ignore(subchunk1Size + 4);
    inAudio.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
    isOpened = true;
    return 0;
}

/**
 * @brief Closes file
 * 
 * @return Error code
 */
int RawAudio::closeFile() {
    inAudio.close();
    isOpened = false;
    return 0;
}

/**
 * @brief Returns audio buffer from beginning, ideal for streaming. This method does NOT open the file stream, which you should do before calling it. You should read in chunks divisible by 4 since each channel is 2 bytes.
 * 
 * @param chunkSize Size in bytes
 * @return Byte array of audio
 */
std::vector<char> RawAudio::getBuffer(uint32_t chunkSize) {
    std::vector<char> buffer (chunkSize, 0);

    if (!inAudio.eof()) {
        inAudio.read(buffer.data(), buffer.size());
    }

    return buffer;
}

/**
 * @brief Returns audio buffer in specified range, ideal for streaming. This method automatically closes and opens file stream. You should read in chunks divisible by 4 since each channel is 2 bytes.
 * 
 * @param startIndex Number of bytes skipped
 * @param chunkSize Size in bytes
 * @return Byte array of audio
 */
std::vector<char> RawAudio::getBufferAt(uint32_t startIndex, uint32_t chunkSize) {
    closeFile();
    openFile();

    std::vector<char> buffer (chunkSize, 0);

    if (!inAudio.eof()) {
        inAudio.ignore(startIndex);
        inAudio.read(buffer.data(), buffer.size());
    }

    return buffer;
}