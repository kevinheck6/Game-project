#pragma once
#include "../States/MainMenuState.h"

class Game {
private:
	//Variables
    sf::Music music;
	GraphicsSettings graphicsSettings;
	StateData DataForStates;
	sf::RenderWindow *window;
	sf::Event event;

    //Time
	sf::Clock dtClock;
	float dt;

    //States
	std::stack<State*> states;

    //Keys
	std::map<std::string, int> supportedKeys;

    //Grid
	float gridSize;

	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initDataForStates();
	void initStates();

public:
    //Constructor
	Game();

    //Destructor
	virtual ~Game();

	static void endApplication();

    //Music
    void playMusic();

    //Updates
	void updateDt();
	void updateEvents();
	void update();

    //Render
	void render();

	//Core of the game
	void run();
};
