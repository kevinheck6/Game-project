#include"../Head Files/PreCompiledHeaders.h"
#include"GraphicsSettings.h"

GraphicsSettings::GraphicsSettings() {
	title = "DEFAULT";
	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	verticalSync = false;
	frameRateLimit = 120;
	contextSettings.antialiasingLevel = 0;
	videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions

void GraphicsSettings::loadFromFile(const std::string& path) {
	std::ifstream ifs(path);

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> resolution.width >> resolution.height;
		ifs >> fullscreen;
		ifs >> frameRateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antialiasingLevel;
	}

	ifs.close();
}