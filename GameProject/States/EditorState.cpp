//
// Created by kevin on 29.10.2021.
//

#include "EditorState.h"

//
// Created by kevin on 22.10.2021.
//
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

    std::ifstream ifs("../Config/EditorState_KeyBinds.ini");
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


EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
        : State(window, supportedKeys, states) {

    this->initBackground();
    this->initVariables();
    this->initFonts();
    this->initKeyBinds();
    this->initButtons();

}

EditorState::~EditorState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}


void EditorState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
        this->endState();
    }
}

void EditorState::updateButtons() {
    //update all buttons on this state and handle their functionality
    for(auto &it : this->buttons) {
        it.second->update(this->mousePosView);
    }
}

void EditorState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInput(dt);

    this->updateButtons();

}

void EditorState::renderButtons(sf::RenderTarget &target) {
    for(auto it : this->buttons) {
        it.second->render(target);
    }
}

void EditorState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }

    this->renderButtons(*target);

    //SEE COORDENATES OF THE MOUSE, NOT INGAME THING
    /*sf::Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(30);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
     */

}
