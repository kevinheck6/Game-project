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
	gfxSettings.loadFromFile("../Config/Graphics_settings.ini");
}

void Game::initWindow() {
	if(gfxSettings.fullscreen) {
        window = new sf::RenderWindow(
                gfxSettings.resolution,
                gfxSettings.title,
                sf::Style::Fullscreen,
                gfxSettings.contextSettings);
    } else {
        window = new sf::RenderWindow(
                gfxSettings.resolution,
                gfxSettings.title,
                sf::Style::Titlebar | sf::Style::Close,
                gfxSettings.contextSettings);

    }

	window->setFramerateLimit(gfxSettings.frameRateLimit);
	window->setVerticalSyncEnabled(gfxSettings.verticalSync);
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

void Game::initStateData() {
	stateData.window = window;
	stateData.gfxSettings = &gfxSettings;
	stateData.supportedKeys = &supportedKeys;
	stateData.states = &states;
	stateData.gridSize = gridSize;
}

void Game::initStates() {
	states.push(new MainMenuState(&stateData));
}

Game::Game() {
	initVariables();
	initGraphicsSettings();
	initWindow();
	initKeys();
	initStateData();
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

void Game::updateSFMLEvents() {
	while (window->pollEvent(sfEvent)) {
		if (sfEvent.type == sf::Event::Closed) {
            window->close();
        }
	}
}

void Game::update() {
	updateSFMLEvents();

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




