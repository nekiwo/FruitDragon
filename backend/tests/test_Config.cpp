#include <gtest/gtest.h>
#include <string>

#include "utils/Config.hpp"


TEST(ConfigTest, IOTest) {
    std::cout << "You need to create a config file for this test." << std::endl;

    Config config;
    std::string homePath = getenv("HOME");
    std::string configPath = homePath.append("/Music/FruitDragon/config.json");
    int error = config.readFromFile(configPath);

    ASSERT_EQ(error, 0);
    ASSERT_TRUE(config.Port > 0);
    ASSERT_TRUE(config.MediaFolderPath.length() > 2);
}