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
    sf::View mainView;

    sf::Font font;
    sf::Text cursorText;
    PauseMenu* pauseMenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    sf::RectangleShape sideBar;

    sf::RectangleShape selectorRect;

    gui::TextureSelector* textureSelector;

    sf::IntRect textureRect;
    bool collision;
    short type;
    float cameraSpeed;

    //Functions
    void initVariables();
    void initView();
    void initBackground();
    void initFonts();
    void initCursorText();
    void initKeyBinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenu();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget &target);
    void render(sf::RenderTarget* target = nullptr);



};

