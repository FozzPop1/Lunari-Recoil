#include "../../inc/macro/config.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

static const fs::path ConfigFolder  = "C:/Lunari/Recoil/Configs";

static inline fs::path GetConfigPath(const std::string& name)
{
    return ConfigFolder / (name + ".cfg");
}

void Config::SetupConfigFolder()
{
    std::error_code ec;
    fs::create_directories(ConfigFolder, ec);
}

void Config::SaveConfig(const std::string& configName)
{
    const fs::path path = GetConfigPath(configName);

    std::ofstream file(path, std::ios::trunc | std::ios::binary);
    if (!file)
        return;

    file.write(reinterpret_cast<const char*>(&RecoilX), sizeof(RecoilX));
    file.write(reinterpret_cast<const char*>(&RecoilY), sizeof(RecoilY));
}

void Config::LoadConfig(const std::string& configName)
{
    const fs::path path = GetConfigPath(configName);

    std::ifstream file(path, std::ios::binary);
    if (!file)
    {
        RecoilX = 0.0f;
        RecoilY = 0.0f;
        return;
    }

    file.read(reinterpret_cast<char*>(&RecoilX), sizeof(RecoilX));
    file.read(reinterpret_cast<char*>(&RecoilY), sizeof(RecoilY));

    if (file.fail())
    {
        RecoilX = 0.0f;
        RecoilY = 0.0f;
    }
}

Config config;