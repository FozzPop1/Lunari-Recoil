#pragma once

#include <string>

class Config {
    private:

    public:

    float RecoilX, RecoilY;

    void SetupConfigFolder();
    
    void SaveConfig(const std::string &ConfigName);
    void LoadConfig(const std::string &ConfigName);
};

extern Config config;