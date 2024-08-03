/**
 * @file Config.hpp
 * @author nekiwo
 * @brief Basic config class to read config.json
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CONFIG
#define CONFIG

#include <filesystem>
#include <string>
#include <unordered_map>

namespace fs = std::filesystem;


class Config {
    public:
        Config();
        fs::path ConfigFolderPath;
        fs::path MediaFolderPath;
        int Port;
        int readFromFolder(fs::path &folderPath);
        int saveCacheMap();
        std::unordered_map<std::string, std::string> TrackCacheMap; // original file -> cache file map
        std::unordered_map<std::string, std::string> IconCacheMap; // collection path -> icon file map
};

#endif