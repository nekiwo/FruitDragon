#include <gtest/gtest.h>
#include <filesystem>
#include <string>

#include "utils/Config.hpp"

namespace fs = std::filesystem;


TEST(ConfigTest, IOTest) {
    Config config;
    std::string configPath = fs::current_path().parent_path() / "tests/config/config.json";
    int error = config.readFromFile(configPath);

    ASSERT_EQ(error, 0);
    ASSERT_EQ(config.Port, 8326);
    ASSERT_TRUE(!fs::is_empty(config.MediaFolderPath));
}