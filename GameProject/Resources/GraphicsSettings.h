#pragma once

class GraphicsSettings {
public:
	GraphicsSettings();

	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullScreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;

	//Functions
	void loadFromFile(const std::string& path);
};

