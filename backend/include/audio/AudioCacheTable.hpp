/**
 * @file AudioCacheTable.hpp
 * @author nekiwo
 * @brief Audio cache table that includes cahced file tree
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef AUDIO_CACHE_TABLE
#define AUDIO_CACHE_TABLE

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;


class AudioCacheTable {
    public:
        AudioCacheTable();
        std::unordered_map<fs::path, fs::path> TrackCacheMap;
};

#endif