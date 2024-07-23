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

#include <fstream>
#include <filesystem>
#include <string>
#include <nlohmann/json.hpp>

#include "utils/Config.hpp"

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
int Config::readFromFile(std::string filePath) {
    std::ifstream in(filePath);
    json data = json::parse(in);
    
    fs::path mediaFolderPathObj(data["mediaPath"]);
    if (mediaFolderPathObj.is_absolute()) {
        this->MediaFolderPath = mediaFolderPathObj;
    } else {
        fs::path filePathObj(filePath);
        this->MediaFolderPath = filePathObj.parent_path() / mediaFolderPathObj; 
    }

    this->Port = data["port"];

    return 0;
}