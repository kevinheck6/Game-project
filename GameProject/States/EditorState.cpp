//
// Created by kevin on 29.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "EditorState.h"
#include "MainMenuState.h"


void EditorState::initVariables() {

}

void EditorState::initBackground() {
}

void EditorState::initFonts() {
    if(!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
        throw("ERROR - EditorState - Could not load");
    }

}

void EditorState::initKeyBinds() {

    std::ifstream ifs("../Config/EditorState_KeyBind.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void EditorState::initButtons() {

}

void EditorState::initPauseMenu() {
    this->pauseMenu = new PauseMenu(*this->window, this->font);
    this->pauseMenu->addButton("EXIT", 500.f, "Exit");
}

void EditorState::initGui() {
    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color::Transparent);
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}


EditorState::EditorState(StateData* state_data)
        : State(state_data) {

    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeyBinds();
    this->initButtons();
    this->initGui();
    this->initPauseMenu();
    this->initTileMap();

}

EditorState::~EditorState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }

    delete this->pauseMenu;
    delete this->tileMap;
}

//Functions
void EditorState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime()) {
        if(!this->pause) {
            this->pauseState();
        } else {
            this->unpauseState();
        }
    }
}

void EditorState::updateButtons() {
    //update all buttons on this state and handle their functionality
    for(auto &it : this->buttons) {
        it.second->update(this->mousePosView);
    }
}

void EditorState::updateGui() {
    this->selectorRect.setPosition(this->mousePosView);
}

void EditorState::updatePauseMenu() {
    if(this->pauseMenu->isButtonPressed("EXIT")) {
        this->endState();
    }
}

void EditorState::update(const float& dt) {
    this->updateMousePosition();
    this->updateKeyTime(dt);
    this->updateInput(dt);

    if(!this->pause) { //Not paused
        this->updateButtons();
        this->updateGui();
    } else { // Paused
        this->pauseMenu->update(this->mousePosView);
        this->updatePauseMenu();
    }
}

void EditorState::renderButtons(sf::RenderTarget &target) {
    for(auto &it : this->buttons) {
        it.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget &target) {
    target.draw(this->selectorRect);
}

void EditorState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }

    this->renderButtons(*target);
    this->renderGui(*target);

    this->tileMap->render(*target);

    if(this->pause) {
        this->pauseMenu->render(*target);
    }

    //SEE COORDENATES OF THE MOUSE, NOT INGAME THING
    sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(30);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);


}











