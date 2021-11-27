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
    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->cameraSpeed = 100.f;

}


void EditorState::initView() {
    this->mainView.setSize(sf::Vector2f(this->stateData->graphSettings->resolution.width,
                                        this->stateData->graphSettings->resolution.height));
    this->mainView.setCenter(this->stateData->graphSettings->resolution.width / 2.f,
                             this->stateData->graphSettings->resolution.height / 2.f);
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
    this->pauseMenu->addButton("EXIT", 600.f, "Exit");
    this->pauseMenu->addButton("LOAD", 400.f, "Load Map");
    this->pauseMenu->addButton("SAVE", 200.f, "Save");
}


void EditorState::initGui() {
    //SETTINGS OF SIDEBAR
    this->sideBar.setPosition(0.f,0.f);
    this->sideBar.setSize(sf::Vector2f(static_cast<float>(this->stateData->graphSettings->resolution.width),
                                       80));
    this->sideBar.setFillColor(sf::Color(50,50,50, 100));
    this->sideBar.setOutlineColor(sf::Color::White);
    this->sideBar.setOutlineThickness(1.f);

    //SETTINGS RECTANGLE IN THE MAP
    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
    this->selectorRect.setOutlineThickness(2.f);
    this->selectorRect.setOutlineColor(sf::Color::Green);

    this->selectorRect.setTexture(this->tileMap->getTileTexture());
    this->selectorRect.setTextureRect(this->textureRect);

    //Editor Screen Texture Position
    this->textureSelector = new gui::TextureSelector(10.f, 10.f, 300.f, 500.f,
                                                     this->stateData->gridSize,
                                                     this->tileMap->getTileTexture(),
                                                     this->font, "Tiles");


}

void EditorState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10,
                                "../Resources/Images/TextureGround/grassSheet.png");
}

EditorState::EditorState(StateData* state_data)
        : State(state_data) {

    this->initVariables();
    this->initView();
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
    //Move View
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_UP")))) {
        this->mainView.move(0.f, -this->cameraSpeed * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_DOWN")))) {
        this->mainView.move(0.f, this->cameraSpeed * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_RIGHT")))) {
        this->mainView.move(this->cameraSpeed * dt, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_CAMERA_LEFT")))) {
        this->mainView.move(-this->cameraSpeed * dt, 0.f);
    }

    //Add Tiles
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime()) {
        if(!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {
            if(!this->textureSelector->getActive()) {
                this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect,
                                       this->collision, this->type);
            } else {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }
    }
    //Remove Tiles
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime()) {
        if(!this->sideBar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))){
            if(!this->textureSelector->getActive()) {
                this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
            }
        }
    }
    //Switch Collision
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("COLLISION_SWITCH"))) &&
        this->getKeyTime()) {
        if(this->collision) {
            collision = false;
        } else {
            collision = true;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TYPE_CHANGE_UP"))) &&
    this->getKeyTime()) {
        this->type++;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TYPE_CHANGE_DOWN"))) &&
            this->getKeyTime()) {
        if (this->type > 0) {
            this->type--;
        }
    }

}

void EditorState::updateButtons() {
    //update all buttons on this state and handle their functionality
    for(auto &it : this->buttons) {
        it.second->update(this->mousePosWindow);
    }
}

void EditorState::updateGui(const float& dt) {
    this->textureSelector->update(this->mousePosWindow, dt);

    //If it's not in the Texture selector screen
    if(!this->textureSelector->getActive()) {
        this->selectorRect.setTextureRect(this->textureRect);
        this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize ,
                                       this->mousePosGrid.y * this->stateData->gridSize);
    }

    this->cursorText.setPosition(this->mousePosView.x + 20, this->mousePosView.y - 50.f);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y << "\n" <<
        this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n" <<
        this->textureRect.left / 100 << " " << this->textureRect.top / 100 << "\n" <<
        "Collision: " << this->collision << "\n" <<
        "Type: " << this->type << "\n";
    this->cursorText.setString(ss.str());

}

void EditorState::updatePauseMenu() {
    if(this->pauseMenu->isButtonPressed("EXIT")) {
        this->endState();
    }
    if(this->pauseMenu->isButtonPressed("SAVE")) {
        this->tileMap->saveFile("SaveMap.mp");
    }
    if(this->pauseMenu->isButtonPressed("LOAD")) {
        this->tileMap->loadFile("../cmake-build-debug/SaveMap.mp");
    }
}

void EditorState::update(const float& dt) {
    this->updateMousePosition(&this->mainView);
    this->updateKeyTime(dt);
    this->updateInput(dt);

    if(!this->pause) { //Not paused
        this->updateButtons();
        this->updateGui(dt);
        this->updateEditorInput(dt);
    } else { // Paused
        this->pauseMenu->update(this->mousePosWindow);
        this->updatePauseMenu();
    }
}

void EditorState::renderButtons(sf::RenderTarget &target) {
    for(auto &it : this->buttons) {
        it.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget &target) {
    if(!this->textureSelector->getActive()) {
        target.setView(this->mainView);
        target.draw(this->selectorRect);
    }
    target.setView(this->window->getDefaultView());
    this->textureSelector->render(target);
    target.draw(this->sideBar);

    target.setView(this->mainView);
    target.draw(this->cursorText);

}

void EditorState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }

    target->setView(this->mainView);
    this->tileMap->render(*target);

    target->setView(this->window->getDefaultView());
    this->renderButtons(*target);
    this->renderGui(*target);

    if(this->pause) {
        target->setView(this->window->getDefaultView());
        this->pauseMenu->render(*target);
    }



}














