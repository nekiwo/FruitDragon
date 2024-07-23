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
int Config::readFromFolder(std::string &folderPath) {
    fs::path folderPathObj(folderPath);

    // Importing config file
    std::ifstream inConfig(folderPathObj / "config.json");
    json configData = json::parse(inConfig);
    
    fs::path mediaFolderPathObj(configData["mediaPath"]);
    if (mediaFolderPathObj.is_absolute()) {
        this->MediaFolderPath = mediaFolderPathObj;
    } else {
        this->MediaFolderPath = folderPathObj / mediaFolderPathObj; 
    }

    this->Port = configData["port"];

    // Importing cache file
    AudioCacheTable cache;
    this->Cache = &cache;

    if (!fs::exists(folderPathObj / "cache.json")) {
        this->Cache->Completed = false;
        return 0;
    }

    std::ifstream inCache(folderPathObj / "cache.json");
    json cacheData = json::parse(inCache);
    
    for (std::string originalFilePath : cacheData["tracks"]) {
        this->Cache->TrackCacheMap[originalFilePath] = (std::string)cacheData["tracks"][originalFilePath];
    }

    for (std::string originalCollectionPath : cacheData["icons"]) {
        this->Cache->IconCacheMap[originalCollectionPath] = (std::string)cacheData["icons"][originalCollectionPath];
    }

    this->Cache->Completed = true;

    return 0;
}