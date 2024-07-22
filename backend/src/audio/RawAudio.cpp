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


RawAudio::RawAudio() {

}

/**
 * @brief Loads the audio metadata into the class object
 * 
 * @param filePath Path to the audio file
 * @return Read error code
 */
int RawAudio::readFromFile(std::string filePath) {

}

/**
 * @brief Loads the audio into the class object, making it accessable through `getBuffer` 
 * 
 * @param filePath Path to the audio file
 * @return Read error code
 */
int RawAudio::loadFromFile(std::string filePath) {

}

/**
 * @brief Returns audio buffer in specified range, ideal for streaming
 * 
 * @param startIndex Byte index
 * @param endIndex Byte index
 * @return Byte array of audio
 */
char* RawAudio::getBuffer(int startIndex, int endIndex) {

}