#include <gtest/gtest.h>
#include <filesystem>
#include <string>

#include "utils/Config.hpp"

namespace fs = std::filesystem;


TEST(ConfigTest, IOTest) {
    fs::path configFolderPath = fs::current_path().parent_path() / "backend/tests/config/";
    fs::remove(configFolderPath / "cache.json");

    Config config;
    int error = config.readFromFolder(configFolderPath);

    ASSERT_NE(error, 2) << "IO Error 2: Config file not found inside " << configFolderPath.string();
    ASSERT_EQ(error, 0) << "IO Error " << std::to_string(error) << ": Unknown error with loading config file.";
    ASSERT_EQ(config.HTTPPort, 8326) << "Config Error: wrong HTTP port number.";
    ASSERT_EQ(config.WSPort, 8327) << "Config Error: wrong WS port number.";
    ASSERT_FALSE(fs::is_empty(config.MediaFolderPath)) << "Config Error: media folder path is empty.";
}