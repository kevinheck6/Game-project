#pragma once
#include "../States/MainMenuState.h"

class Game {
private:
	//Variables
    sf::Music music;
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

public:
	Game();
	virtual ~Game();

	static void endApplication();

    void playMusic();
	void updateDt();
	void updateSFMLEvents();
	void update();

	void render();

	//Core
	void run();
};
