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
#include <string>
#include <nlohmann/json.hpp>

#include "utils/Config.hpp"

using json = nlohmann::json;


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

    this->MediaFolderPath = data["mediaPath"];
    this->Port = data["port"];

    return 0;
}