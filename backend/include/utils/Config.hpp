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

namespace fs = std::filesystem;


class Config {
    public:
        Config();
        fs::path MediaFolderPath;
        int Port;
        int readFromFile(std::string filePath);
};

#endif