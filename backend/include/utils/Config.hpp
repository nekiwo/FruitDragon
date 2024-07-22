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

#include <string>


class Config {
    public:
        Config();
        std::string MediaFolderPath;
        int Port;
        int readFromFile(std::string filePath);
};

#endif