#pragma once

#include "State.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"

class GameState :
    public State {

private:
    PauseMenu* pauseMenu;
    sf::Font font;

    Player* player;
    sf::Texture texture;

    TileMap map;

    //Functions
    void initKeyBinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();

public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

 //Functions
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};



