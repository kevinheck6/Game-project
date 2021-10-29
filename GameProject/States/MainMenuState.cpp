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

    this->buttons["GAME_STATE"] = new Button(
            620.f,300.f, 150.f, 50.f,
            &this->font,"New Game", 70,
            sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(150, 20, 20, 0));

    this->buttons["SETTINGS_STATE"] = new Button(
            620.f,400.f, 150.f, 50.f,
            &this->font,"Game Settings",70,
            sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["EDITOR_STATE"] = new Button(
            620.f,500.f, 150.f, 50.f,
            &this->font,"EDITOR",70,
            sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["EXIT_STATE"] = new Button(
            620.f,600.f, 150.f, 50.f,
            &this->font,"Exit game",70,
            sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
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

    //Settings

    //Editor
    if(this->buttons["EDITOR_STATE"]->isPressed()) {
        this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
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










