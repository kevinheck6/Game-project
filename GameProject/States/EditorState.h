//
// Created by kevin on 29.10.2021.
//
#pragma once

#include "State.h"
#include "../Resources/Button.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"

class State;
class Button;
class PauseMenu;
class TileMap;

class EditorState :
        public State {
private:
    //Variables
    sf::Font font;
    PauseMenu* pauseMenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    sf::RectangleShape selectorRect;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeyBinds();
    void initButtons();
    void initPauseMenu();
    void initGui();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui();
    void updatePauseMenu();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget &target);
    void render(sf::RenderTarget* target = nullptr);



};

