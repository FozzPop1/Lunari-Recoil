#include "../../inc/macro/config.h"

#include <fstream>
#include <filesystem>

/*
    Base Config System
*/

void Config::SetupConfigFolder() {
    std::filesystem::create_directory("configs");
}

void Config::SaveConfig(const std::string &ConfigName) {
    std::ofstream config("configs\\" + ConfigName + ".cfg");

    if (!config.is_open())
        return;

    config << Config::RecoilX << '\n';
    config << Config::RecoilY << '\n';
}

void Config::LoadConfig(const std::string &ConfigName)
{
    std::ifstream config("configs/" + ConfigName);

    if (!config)
        return;

    config >> Config::RecoilX;
    config >> Config::RecoilY;
}

Config config;