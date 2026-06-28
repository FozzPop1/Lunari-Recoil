#include "../../inc/macro/config.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// Better: relative to executable / working directory instead of hardcoding C:
static const fs::path ConfigFolder = fs::path("C:/Lunari") / "Recoil" / "Configs";

static inline fs::path GetConfigPath(const std::string& name)
{
    return ConfigFolder / (name + ".cfg");
}

void Config::SetupConfigFolder()
{
    std::error_code ec;
    fs::create_directories(ConfigFolder, ec);

    // optional: you can silently ignore or log ec
}

void Config::SaveConfig(const std::string& configName)
{
    const fs::path path = GetConfigPath(configName);

    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    if (!file.is_open())
        return;

    file.write(reinterpret_cast<const char*>(&RecoilX), sizeof(RecoilX));
    file.write(reinterpret_cast<const char*>(&RecoilY), sizeof(RecoilY));
    file.write(reinterpret_cast<const char*>(&SmoothingX), sizeof(SmoothingX));
    file.write(reinterpret_cast<const char*>(&SmoothingY), sizeof(SmoothingY));
    file.write(reinterpret_cast<const char*>(&Humanize), sizeof(Humanize));

    file.close();
}

void Config::LoadConfig(const std::string& configName)
{
    const fs::path path = GetConfigPath(configName);

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        RecoilX = RecoilY = 0.0f;
        SmoothingX = SmoothingY = 0.0f;
        Humanize = 0.0f;
        return;
    }

    file.read(reinterpret_cast<char*>(&RecoilX), sizeof(RecoilX));
    file.read(reinterpret_cast<char*>(&RecoilY), sizeof(RecoilY));
    file.read(reinterpret_cast<char*>(&SmoothingX), sizeof(SmoothingX));
    file.read(reinterpret_cast<char*>(&SmoothingY), sizeof(SmoothingY));
    file.read(reinterpret_cast<char*>(&Humanize), sizeof(Humanize));

    if (file.gcount() <= 0 || file.fail())
    {
        RecoilX = RecoilY = 0.0f;
        SmoothingX = SmoothingY = 0.0f;
        Humanize = 0.0f;
    }
}

Config config;