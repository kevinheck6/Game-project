//
// Created by kevin on 22.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "GameState.h"

//Initializer

void GameState::initKeyBinds() {

    std::ifstream ifs("../Config/GameState_KeyBind.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void GameState::initFonts() {
    if(!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
        throw("ERROR - MainMenuState - Could not load");
    }

}

void GameState::initTextures() {
    if(!this->textures["PLAYER_SHEET"].loadFromFile("../Resources/Images/Sprites/Player/Idle3.png")) {
        throw "ERROR - GAMESTATE::InitTextures FAIL TO LOAD PLAYER_IDLE TEXTURE";
    }
}

void GameState::initPauseMenu() {
    this->pauseMenu = new PauseMenu(*this->window, this->font);
    this->pauseMenu->addButton("EXIT", 500.f, "Exit");
}

void GameState::initPlayers() {
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}


//Constructors
GameState::GameState(StateData* state_data)
    : State(state_data) {
    this->initKeyBinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayers();
    this->initTileMap();
}

GameState::~GameState() {
    delete this->pauseMenu;
    delete this->player;
    delete this->tileMap;
}

void GameState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime()) {
        if(!this->pause) {
            this->pauseState();
            std::cout << "paused";
        } else {
         this->unpauseState();
        }
    }
}

void GameState::updatePlayerInput(const float &dt) {

    //playerInput
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {
        this->player->move(-1.f, 0.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {
        this->player->move(1.f, 0.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) {
        this->player->move(0.f, -1.f, dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {
        this->player->move(0.f, 1.f, dt);
    }
}

void GameState::updatePauseMenuButtons() {
    if(this->pauseMenu->isButtonPressed("EXIT")) {
        this->endState();
    }
}

void GameState::update(const float& dt) {
    this->updateMousePosition();
    this->updateKeyTime(dt);
    this->updateInput(dt);

    if(!this->pause) { // Unpause
        this->updatePlayerInput(dt);

        this->player->update(dt);
    } else { // Pause update
        this->pauseMenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }
    //Render map Tile
    //this->map.render(*target); TURN THIS ON LATER
    //Render player
    this->player->render(*target);
    //Render pause menu
    if(this->pause) {
        this->pauseMenu->render(*target);
    }
}













