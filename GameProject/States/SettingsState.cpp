//
// Created by kevin on 14.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "SettingsState.h"

//Private Functions
void SettingsState::initVariables() {
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground() {
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));


    if(!this->backgroundTexture.loadFromFile("../Resources/Images/Background/MainMenuImage.png")) {
        throw "ERROR - MAIN MENU STATE FAIL TO LOAD BACKGROUND TEXTURE";
    }
    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts() {
    if(!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
        throw("ERROR - MainMenuState - Could not load");
    }

}

void SettingsState::initKeyBinds() {

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

void SettingsState::initButtons() {
    this->buttons["EXIT_STATE"] = new gui::Button(
            820.f,600.f, 150.f, 50.f,
            &this->font,"Main Menu",70,
            sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["APPLY"] = new gui::Button(
            420.f,600.f, 150.f, 50.f,
            &this->font,"Apply Changes",70,
            sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));


    std::vector<std::string> video_modes_str;
    for(auto &i : this->videoModes) {
        video_modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->dropDownLists["RESOLUTION"] = new gui::DropDownList(200, 190, 200, 50, font,
                                                              video_modes_str.data(), video_modes_str.size());
}

void SettingsState::initText() {
    this->optionsText.setFont(this->font);

    this->optionsText.setPosition(sf::Vector2f(100.f, 200.f));
    this->optionsText.setCharacterSize(30.f);
    this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

    this->optionsText.setString("Resolution \n\n\nFullScreen\n\n\nVsync \n\n\nAntialiasing \n");
}

SettingsState::SettingsState(sf::RenderWindow* window, GraphSettings& graphSettings,
                             std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : State(window, supportedKeys, states), graphSettings(graphSettings) {

    this->initBackground();
    this->initVariables();
    this->initFonts();
    this->initKeyBinds();
    this->initButtons();
    this->initText();

}

SettingsState::~SettingsState() {
    auto it = this->buttons.begin();
    auto it2 = this->dropDownLists.begin();

    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2) {
        delete it2->second;
    }
}

//Accessors

//Functions
void SettingsState::updateInput(const float &dt) {

}

void SettingsState::updateButtons(const float& dt) {
    //update all elements on this state and handle their functionality

    //Buttons
    for(auto &it : this->buttons) {
        it.second->update(this->mousePosView);
    }
    //Functionality
    //Quit The Game
    if(this->buttons["EXIT_STATE"]->isPressed()) {
        this->endState();
    }

    //Apply the changes made in settings
    if(this->buttons["APPLY"]->isPressed()) {

        //TESTING REMOVE
        this->graphSettings.resolution = this->videoModes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
        this->window->create(this->graphSettings.resolution, this->graphSettings.title,
                             sf::Style::Default);
    }

    //Dropdown lists Part
    for(auto &it : this->dropDownLists) {
        it.second->update(this->mousePosView, dt);
    }
}

void SettingsState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInput(dt);

    this->updateButtons(dt);

}

void SettingsState::renderButtons(sf::RenderTarget &target) {
    for(auto &it : this->buttons) {
        it.second->render(target);
    }

    for(auto &it : this->dropDownLists) {
        it.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget* target) {
    if(!target) {
        target = this->window;
    }
    target->draw(this->background);

    this->renderButtons(*target);

    target->draw(this->optionsText);


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


