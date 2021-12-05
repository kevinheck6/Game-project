#include "../Head Files/PreCompiledHeaders.h"
#include "../States/GameState.h"

void GameState::initDeferredRender() {
	renderTexture.create(
		stateData->gfxSettings->resolution.width,
		stateData->gfxSettings->resolution.height);

	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(
		sf::IntRect(0,0,
			static_cast<int>(stateData->gfxSettings->resolution.width),
			static_cast<int>(stateData->gfxSettings->resolution.height)));
}

//Initializer functions
void GameState::initView() {
    view.setSize(sf::Vector2f(
			static_cast<float>(stateData->gfxSettings->resolution.width),
			static_cast<float>(stateData->gfxSettings->resolution.height)));

	view.setCenter(sf::Vector2f(
			static_cast<float>(stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(stateData->gfxSettings->resolution.height) / 2.f));
}

void GameState::initKeybinds() {
	std::ifstream ifs("../Config/GameState_Keys.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
			keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void GameState::initFonts() {
	if (!font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
		throw("ERROR - GameState - Was not able to load the Font");
	}
}

void GameState::initTextures() {
	if (!this->textures["PLAYER_SHEET"].loadFromFile("../Resources/Images/Sprites/Player/Idle3.png")) {
		throw "ERROR - GameState - Was not able to load the Player Texture";
	}
}

void GameState::initPauseMenu() {
	pmenu = new PauseMenu(*window, font);
	pmenu->addButton("EXIT", 500.f, "Exit");
}

void GameState::initPlayers() {
	player = new Player(0, 0, textures["PLAYER_SHEET"]);
}

void GameState::initTileMap() {
	tileMap = new TileMap(stateData->gridSize,
                          1000, 1000,
                          "../Resources/Images/TextureGround/grassSheet.png");
	tileMap->loadFromFile("../Map/text.slmp");
}

void GameState::initButtons() {
    this->buttons["STATE_EXIT"] = new gui::Button(
            1000.f,650.f, 150.f, 68.f,
            &this->font,"Exit game",70,
            sf::Color(250, 70, 70, 200),
            sf::Color(250, 250, 250, 250),
            sf::Color(20, 20, 20, 50),

            sf::Color(70, 70, 70, 0),
            sf::Color(150, 150, 150, 0),
            sf::Color(20, 20, 20, 0));

}

GameState::GameState(StateData* state_data)
	: State(state_data) {
	initDeferredRender();
	initView();
	initKeybinds();
    initButtons();
	initFonts();
	initTextures();
	initPauseMenu();

	initPlayers();
	initTileMap();
}

GameState::~GameState() {
	delete pmenu;
	delete player;
	delete tileMap;

    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it) {
        delete it->second;
    }
}

//Functions

void GameState::updateEndgame(int gameState) {
    this->endGame = gameState;
    std::cout << endGame;
}

void GameState::updateButtons() {
    for (auto &it : buttons) {
        it.second->update(this->mousePosWindow);
    }

    if (buttons["STATE_EXIT"]->isPressed()) {
        endState();
    }
}

void GameState::updateView(const float & dt) {
	view.setCenter(std::floor(player->getPosition().x), std::floor(player->getPosition().y));
}

void GameState::updateInput(const float & dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("EXIT"))) &&
    getKeytime()) {
		if (!paused) {
            pauseState();
        } else {
            unpauseState();
        }
	}
}

void GameState::updatePlayerInput(const float & dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("LEFT_MOVEMENT")))) {
        player->move(-1.f, 0.f, dt);
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("RIGHT_MOVEMENT")))) {
        player->move(1.f, 0.f, dt);
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("UP_MOVEMENT")))) {
        player->move(0.f, -1.f, dt);
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("DOWN_MOVEMENT")))) {
        player->move(0.f, 1.f, dt);
    }
}

void GameState::updatePauseMenuButtons() {
	if (pmenu->isButtonPressed("EXIT")) {
        endState();
    }
}

void GameState::updateTileMap(const float & dt) {
	tileMap->update();
	tileMap->updateCollision(player, dt);
    tileMap->updateType(player, dt);
    updateEndgame(tileMap->updateEndGame());
}

void GameState::update(const float& dt) {
	updateMousePositions(&view);
	updateKeytime(dt);
	updateInput(dt);
    updateButtons();// crashing

	
	if (!paused) {
		updateView(dt);
		updatePlayerInput(dt);
		updateTileMap(dt);
		player->update(dt);
	} else {
		pmenu->update(this->mousePosWindow);
		updatePauseMenuButtons();
	}
}

void GameState::renderButtons(sf::RenderTarget &target) {
    if(this->endGame) {
        for (auto &it : buttons) {
            it.second->render(target);
        }
    }
}


void GameState::render(sf::RenderTarget* target) {
	if (!target) {
        target = window;
    }
	renderTexture.clear();

	renderTexture.setView(view);
	tileMap->render(renderTexture, player->getGridPosition(
            static_cast<int>(stateData->gridSize)));

	player->render(renderTexture);

	tileMap->renderDeferred(renderTexture);

	if (paused) {
		renderTexture.setView(renderTexture.getDefaultView());
		pmenu->render(renderTexture);
	}

	this->renderTexture.display();
	target->draw(renderSprite);
    renderButtons(*target);
}








