//
// Created by kevin on 29.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "EditorState.h"
#include "MainMenuState.h"


void EditorState::initVariables() {
    this->textureRect = sf::IntRect (0, 0,
                                      static_cast<int>(this->stateData->gridSize),
                                      static_cast<int>(this->stateData->gridSize));

}

void EditorState::initBackground() {
}

void EditorState::initFonts() {
    if(!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
        throw("ERROR - EditorState - Could not load");
    }

}

void EditorState::initCursorText() {
    //SEE COORDENATES OF THE MOUSE
    this->cursorText.setFont(this->font);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setCharacterSize(20);
    this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y);
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

void EditorState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

void EditorState::initGui() {
    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);

    this->selectorRect.setTexture(this->tileMap->getTileTexture());
    this->selectorRect.setTextureRect(this->textureRect);

    this->textureSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f,
                                                     this->tileMap->getTileTexture());
}

EditorState::EditorState(StateData* state_data)
        : State(state_data) {

    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initCursorText();
    this->initKeyBinds();
    this->initButtons();
    this->initPauseMenu();
    this->initTileMap();
    this->initGui();

}

EditorState::~EditorState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }

    delete this->pauseMenu;
    delete this->tileMap;
    delete this->textureSelector;
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

void EditorState::updateEditorInput(const float &dt) {
    //Add Tiles
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()) {
        this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
    }
    //Remove Tiles
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime()) {
        this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
    }
    //Change Tiles
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->getKeyTime()) {
        if(this->textureRect.left < 100) {
            this->textureRect.left += 100;
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
    this->selectorRect.setTextureRect(this->textureRect);
    this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize,
                                   this->mousePosGrid.y * this->stateData->gridSize);

    this->cursorText.setPosition(this->mousePosView.x + 20, this->mousePosView.y - 50.f);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y << "\n" <<
        this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n" <<
        this->textureRect.left / 100 << " " << this->textureRect.top / 100;
    this->cursorText.setString(ss.str());

    this->textureSelector->update();
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
        this->updateEditorInput(dt);
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
    this->textureSelector->render(target);
    target.draw(this->cursorText);

}

void EditorState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }

    this->tileMap->render(*target);
    this->renderButtons(*target);
    this->renderGui(*target);

    if(this->pause) {
        this->pauseMenu->render(*target);
    }



}













