//
// Created by kevin on 22.10.2021.
//
#include "MainMenuState.h"


void MainMenuState::initVariables() {

}

void MainMenuState::initBackground() {
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));


    if(!this->backgroundTexture.loadFromFile("../Resources/Images/Background/MainMenuImage.png")) {
        throw "ERROR - MAIN MENU STATE FAIL TO LOAD BACKGROUND TEXTURE";
    }
    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts() {
    if(!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
        throw("ERROR - MainMenuState - Could not load");
    }

}

void MainMenuState::initKeyBinds() {

    std::ifstream ifs("../Config/MainMenuState_KeyBinds.ini");
    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void MainMenuState::initButtons() {

    this->buttons["GAME_STATE"] = new Button(620,300, 150, 50,
                                                    &this->font,"New Game",
                                     sf::Color(70, 70, 150, 200),
                                     sf::Color(70, 200, 200, 200),
                                     sf::Color(150, 70, 150, 200));

    this->buttons["SETTINGS_STATE"] = new Button(620,400, 150, 50,
                                             &this->font,"Game Settings",
                                             sf::Color(70, 70, 150, 200),
                                             sf::Color(70, 200, 200, 200),
                                             sf::Color(150, 70, 150, 200));

    this->buttons["EXIT_STATE"] = new Button(620,500, 150, 50,
                                             &this->font,"Exit game",
                                             sf::Color(70, 70, 150, 200),
                                             sf::Color(70, 200, 200, 200),
                                             sf::Color(150, 70, 150, 200));
}


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
        : State(window, supportedKeys, states) {

    this->initBackground();
    this->initVariables();
    this->initFonts();
    this->initKeyBinds();
    this->initButtons();

}

MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}


void MainMenuState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
        this->endState();
    }
}

void MainMenuState::updateButtons() {
    //update all buttons on this state and handle their functionality
    for(auto &it : this->buttons) {
        it.second->update(this->mousePosView);
    }
    //New Game
    if(this->buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    //Quit The Game
    if(this->buttons["EXIT_STATE"]->isPressed()) {
        this->endState();
    }
}

void MainMenuState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInput(dt);

    this->updateButtons();

}

void MainMenuState::renderButtons(sf::RenderTarget *target) {
    for(auto it : this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }
    target->draw(this->background);

    this->renderButtons(target);

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










