//
// Created by kevin on 22.10.2021.
//

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

void GameState::initTextures() {
    if(!this->textures["PLAYER_SHEET"].loadFromFile("../Resources/Images/Sprites/Player/Idle2.png")) {
        throw "ERROR - GAMESTATE::InitTextures FAIL TO LOAD PLAYER_IDLE TEXTURE";
    }
}


void GameState::initPlayers() {
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}


//Constructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states) {
    this->initKeyBinds();
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState() {
    delete this->player;
}


void GameState::updateInput(const float &dt) {

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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
        this->endState();
    }
}

void GameState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInput(dt);
    this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
        this->player->render(*target);
    }
}






