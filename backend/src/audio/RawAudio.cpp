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
    std::cout << this->AudioFilePath.string() << std::endl;
    inAudio.open(this->AudioFilePath, std::ios::binary);
    inAudio.ignore(16);
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
 * @brief Returns audio buffer in specified range, ideal for streaming
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
 * @brief Returns audio buffer in specified range, ideal for streaming (closes and opens file before doing so)
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