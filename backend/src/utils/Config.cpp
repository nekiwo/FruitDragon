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

#include "utils/Config.hpp"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;


Config::Config() {

}

/**
 * @brief Reads config from JSON file
 * 
 * @param filePath Path to file
 * @return Read error code
 */
int Config::readFromFolder(fs::path &folderPath) {
    ConfigFolderPath = folderPath;

    // Importing config file
    if (!fs::exists(folderPath / "config.json")) {
        return 1;
    }
    std::ifstream inConfig(folderPath / "config.json");
    json configData = json::parse(inConfig);
    
    fs::path mediaFolderPathObj(configData["mediaPath"]);
    if (mediaFolderPathObj.is_absolute()) {
        this->MediaFolderPath = mediaFolderPathObj;
    } else {
        this->MediaFolderPath = folderPath / mediaFolderPathObj; 
    }

    this->Port = configData["port"];

    // Read cache
    if (!fs::exists(folderPath / "cache.json")) {
        std::ofstream outCache(folderPath / "cache.json");
        outCache << "{}";
        outCache.close();
        return 0;
    }
    std::ifstream inCache(folderPath / "cache.json");
    json cacheData;
    try {
        cacheData = json::parse(inCache);
    } catch(json::parse_error& error) {
        // Empty file, no handling necessary
        return 0;
    }
    
    for (auto& filePathPair : cacheData["tracks"].items()) {
        this->TrackCacheMap[filePathPair.key()] = (std::string)filePathPair.value();
    }

    for (auto& iconPathPair : cacheData["icons"].items()) {
        this->IconCacheMap[iconPathPair.key()] = (std::string)iconPathPair.value();
    }

    return 0;
}

/**
 * @brief Saves cache maps into JSON file
 * 
 * @return Error code
 */
int Config::saveCacheMap() {
    // TODO: IO error handling
    if (!fs::exists(ConfigFolderPath / "cache.json")) {
        return 2;
    }
    std::ifstream inCache(ConfigFolderPath / "cache.json");
    std::ofstream outCache(ConfigFolderPath / "cache.json");


    json cacheData;
    try {
        cacheData = json::parse(inCache);
    } catch(json::parse_error& error) {
        // Empty file, no handling necessary
    }

    for (const auto& [originalTrackPath, cachedTrackPath] : TrackCacheMap) {
        cacheData["tracks"][originalTrackPath] = cachedTrackPath;
    }

    for (const auto& [originalIconPath, cachedIconPath] : IconCacheMap) {
        cacheData["icons"][originalIconPath] = cachedIconPath;
    }

    outCache << cacheData;
    outCache.close();

    return 0;
}