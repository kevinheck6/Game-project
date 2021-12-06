#include "../Head Files/PreCompiledHeaders.h"
#include "../Resources/GraphicsSettings.h"

GraphicsSettings::GraphicsSettings() {
	title = "GAMU";
	resolution = sf::VideoMode::getDesktopMode();
    fullScreen = false;
	verticalSync = false;
	frameRateLimit = 90;
	contextSettings.antialiasingLevel = 0;
}

//Functions

void GraphicsSettings::loadFromFile(const std::string& path) {
	std::ifstream ifs(path);

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> resolution.width >> resolution.height;
		ifs >> fullScreen;
		ifs >> frameRateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antialiasingLevel;
	}

	ifs.close();
}