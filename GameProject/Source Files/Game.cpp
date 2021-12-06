#include "../Head Files/PreCompiledHeaders.h"
#include "../Head Files/Game.h"

//Static functions

//Initializer functions
void Game::initVariables() {
	window = nullptr;
	dt = 0.f;
	gridSize = 32.f; // Maybe change for more or less quality and art style
}

void Game::initGraphicsSettings() {
	graphicsSettings.loadFromFile("../Config/Graphics_settings.ini");
}

void Game::initWindow() {
	if(graphicsSettings.fullScreen) {
        window = new sf::RenderWindow(
                graphicsSettings.resolution,
                graphicsSettings.title,
                sf::Style::Fullscreen,
                graphicsSettings.contextSettings);
    } else {
        window = new sf::RenderWindow(
                graphicsSettings.resolution,
                graphicsSettings.title,
                sf::Style::Titlebar | sf::Style::Close,
                graphicsSettings.contextSettings);

    }

	window->setFramerateLimit(graphicsSettings.frameRateLimit);
	window->setVerticalSyncEnabled(graphicsSettings.verticalSync);
}

void Game::initKeys() {
	std::ifstream ifs("../Config/Supported_keys.ini");

	if (ifs.is_open()) {
		std::string key;
		int key_value = 0;
		
		while (ifs >> key >> key_value) {
			supportedKeys[key] = key_value;
		}
	}

	ifs.close();

}

void Game::initDataForStates() {
    DataForStates.window = window;
    DataForStates.graphicsSettings = &graphicsSettings;
    DataForStates.supportedKeys = &supportedKeys;
    DataForStates.states = &states;
    DataForStates.gridSize = gridSize;
}

void Game::initStates() {
	states.push(new MainMenuState(&DataForStates));
}

Game::Game() {
	initVariables();
	initGraphicsSettings();
	initWindow();
	initKeys();
    initDataForStates();
	initStates();
}

Game::~Game() {
	delete window;

	while (!states.empty()) {
		delete states.top();
		states.pop();
	}
}

//Functions
void Game::endApplication() {
	std::cout << "Game closed" << "\n";
}


void Game::playMusic() {
    if(!music.openFromFile("../Resources/Music .wav")) {
        throw "ERROR - Game.cpp - Failled to load Music";
    }
    music.setVolume(30);
    music.play();
    music.setLoop(true);
}

void Game::updateDt() {
    //dt variable will be updated with the time it will take to render one frame, so it will be constant
	dt = dtClock.restart().asSeconds();
}

void Game::updateEvents() {
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
            window->close();
        }
	}
}

void Game::update() {
    updateEvents();

	if (!states.empty()) {
		if (window->hasFocus()) {
			states.top()->update(dt);
			if (states.top()->getQuit()) {
				states.top()->endState();
				delete states.top();
				states.pop();
			}
		}
	} else {
		endApplication();
		window->close();
	}
}

void Game::render() {
	window->clear();
	if (!states.empty()) {
        states.top()->render();
    }
	window->display();
}

void Game::run() {

    playMusic();
	while (window->isOpen()) {
		updateDt();
		update();
		render();

	}
}




