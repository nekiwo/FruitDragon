#include <gtest/gtest.h>
#include <filesystem>
#include <string>

#include "utils/Config.hpp"

namespace fs = std::filesystem;


TEST(ConfigTest, IOTest) {
    Config config;
    std::string configFolderPath = fs::current_path().parent_path() / "tests/config/";
    int error = config.readFromFolder(configFolderPath);

    ASSERT_EQ(error, 0);
    ASSERT_EQ(config.Port, 8326);
    ASSERT_TRUE(!fs::is_empty(config.MediaFolderPath));
}