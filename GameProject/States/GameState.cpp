#include "../Head Files/PreCompiledHeaders.h"
#include "../States/GameState.h"

void GameState::initBackground() {
    background.setSize(sf::Vector2f(
            static_cast<float>(window->getSize().x),
            static_cast<float>(window->getSize().y)));
    background.setFillColor(sf::Color::White);
}

void GameState::initDeferredRender() {
	renderTexture.create(
            DataForStates->graphicsSettings->resolution.width,
            DataForStates->graphicsSettings->resolution.height);

	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(
		sf::IntRect(0,0,
			static_cast<int>(DataForStates->graphicsSettings->resolution.width),
			static_cast<int>(DataForStates->graphicsSettings->resolution.height)));
}

void GameState::initView() {
    view.setSize(sf::Vector2f(
			static_cast<float>(DataForStates->graphicsSettings->resolution.width),
			static_cast<float>(DataForStates->graphicsSettings->resolution.height)));

	view.setCenter(sf::Vector2f(
            static_cast<float>(DataForStates->graphicsSettings->resolution.width) / 2.f,
            static_cast<float>(DataForStates->graphicsSettings->resolution.height) / 2.f));
}

void GameState::initKeyBinds() {
	std::ifstream ifs("../Config/GameState_Keys.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
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
    pauseMenu = new PauseMenu(*window, font);
	pauseMenu->addButton("EXIT", 500.f, "Exit");
}

void GameState::initPlayers() {
	player = new Player(0, 0, textures["PLAYER_SHEET"]);
}

void GameState::initTileMap() {
	tileMap = new TileMap(DataForStates->gridSize,
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

    initBackground();
	initDeferredRender();
	initView();
    initKeyBinds();
    initButtons();
	initFonts();
	initTextures();
	initPauseMenu();

	initPlayers();
	initTileMap();
}

GameState::~GameState() {
	delete pauseMenu;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("EXIT"))) &&
            getTimeKey()) {
		if (!paused) {
            pauseState();
        } else {
            unpauseState();
        }
	}
}

void GameState::updatePlayerInput(const float & dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("LEFT_MOVEMENT")))) {
        player->move(-1.f, 0.f, dt);
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("RIGHT_MOVEMENT")))) {
        player->move(1.f, 0.f, dt);
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("UP_MOVEMENT")))) {
        player->move(0.f, -1.f, dt);
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("DOWN_MOVEMENT")))) {
        player->move(0.f, 1.f, dt);
    }
}

void GameState::updatePauseMenuButtons() {
	if (pauseMenu->ButtonPressed("EXIT")) {
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
    updateTimeKey(dt);
	updateInput(dt);
    updateButtons();

	
	if (!paused) {
		updateView(dt);
		updatePlayerInput(dt);
		updateTileMap(dt);
		player->update(dt);
	} else {
		pauseMenu->update(this->mousePosWindow);
		updatePauseMenuButtons();
	}
}

void GameState::renderButtons(sf::RenderTarget &target) {
    if(this->endGame) {
        for (auto &it : buttons) {
            target.draw(background);
            it.second->render(target);
        }
        text.setFont(font);
        text.setString("You Won The Labyrinth");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setPosition(static_cast<float>(window->getSize().x) / 2,
                         static_cast<float>(window->getSize().y) / 2);
        target.draw(text);
    }
}


void GameState::render(sf::RenderTarget* target) {
	if (!target) {
        target = window;
    }
	renderTexture.clear();

	renderTexture.setView(view);
	tileMap->render(renderTexture, player->getGridPosition(
            static_cast<int>(DataForStates->gridSize)));

	player->render(renderTexture);

	tileMap->renderDeferred(renderTexture);

	if (paused) {
		renderTexture.setView(renderTexture.getDefaultView());
		pauseMenu->render(renderTexture);
	}

	this->renderTexture.display();
	target->draw(renderSprite);

    renderButtons(*target);

}











