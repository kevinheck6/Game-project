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

    TileMap* tileMap;

    //Functions
    void initKeyBinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

 //Functions
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};



