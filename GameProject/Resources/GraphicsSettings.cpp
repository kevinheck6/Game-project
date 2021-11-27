//
// Created by kevin on 20.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"

#include "GraphicsSettings.h"

//Class Graph Settings
GraphSettings::GraphSettings() {
    this->title = "DEFAULT_TITLE";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullScreen = false;
    this->verticalSync = false;
    this->frameRateLimit = 90;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

GraphSettings::~GraphSettings() {

}

//Functions
void GraphSettings::saveFile(const std::string path) {
    std::ofstream ofs(path);

    if(ofs.is_open()) {
        ofs << this->title;
        ofs << this->resolution.width << " " << this->resolution.height;
        ofs << this->fullScreen;
        ofs << this->frameRateLimit;
        ofs << this->verticalSync;
        ofs << this->contextSettings.antialiasingLevel;
    }
    ofs.close();
}

void GraphSettings::loadFile(const std::string path) {
    std::ifstream ifs(path);

    if(ifs.is_open()) {
        std::getline(ifs, this->title);
        ifs >> this->resolution.width >> this->resolution.height;
        ifs >> this->fullScreen;
        ifs >> this->frameRateLimit;
        ifs >> this->verticalSync;
        ifs >> this->contextSettings.antialiasingLevel;
    }
    ifs.close();
}

