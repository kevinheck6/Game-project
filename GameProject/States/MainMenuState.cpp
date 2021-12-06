#include "../Head Files/PreCompiledHeaders.h"
#include "../States/MainMenuState.h"

//Initializer functions
void MainMenuState::initVariables() {}

void MainMenuState::initBackground() {
	background.setSize(sf::Vector2f(
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y)));
	
	if (!backgroundTexture.loadFromFile("../Resources/Images/Background/MainMenuImage.png")) {
		throw "ERROR - MainMenuState.cpp - Failed to load the background";
	}
	background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts() {
	if (!font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
		throw("ERROR - MainMenuState.cpp - Failed to load the Font");
	}
}

void MainMenuState::initKeyBinds() {
	std::ifstream ifs("../Config/MainMenuState_KeyBinds.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void MainMenuState::initButtons() {
    this->buttons["STATE_INGAME"] = new gui::Button(
            100.f,650.f, 150.f, 68.f,
            &this->font,"New Game", 70,
            sf::Color(250, 70, 70, 200),
            sf::Color(250, 250, 250, 250),
            sf::Color(20, 20, 20, 50),

            sf::Color(70, 70, 70, 0),
            sf::Color(150, 150, 150, 0),
            sf::Color(150, 20, 20, 0));


    this->buttons["STATE_EDITOR"] = new gui::Button(
            800.f,650.f, 150.f, 68.f,
            &this->font,"EDITOR",70,
            sf::Color(250, 70, 70, 200),
            sf::Color(250, 250, 250, 250),
            sf::Color(20, 20, 20, 50),

            sf::Color(70, 70, 70, 0),
            sf::Color(150, 150, 150, 0),
            sf::Color(20, 20, 20, 0));

    this->buttons["STATE_EXIT"] = new gui::Button(
            1000.f,650.f, 150.f, 68.f,
            &this->font,"Exit game",70,
            sf::Color(250, 70, 70, 200),
            sf::Color(250, 250, 250, 250),
            sf::Color(20, 20, 20, 50),

            sf::Color(70, 70, 70, 0),
            sf::Color(150, 150, 150, 0),
            sf::Color(20, 20, 20, 0));
}

MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data) {
	initVariables();
	initBackground();
	initFonts();
    initKeyBinds();
	initButtons();
}

MainMenuState::~MainMenuState() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}


void MainMenuState::updateInput(const float & dt) {}

void MainMenuState::updateButtons() {
    //Update buttons

	for (auto &it : buttons) {
		it.second->update(this->mousePosWindow);
	}
	//For the game
	if (buttons["STATE_INGAME"]->isPressed()) {
		states->push(new GameState(DataForStates));
	}

	//Editor State
	if (buttons["STATE_EDITOR"]->isPressed()) {
		states->push(new EditorState(DataForStates));
	}

	//Exit
	if (buttons["STATE_EXIT"]->isPressed()) {
		endState();
	}
}

void MainMenuState::update(const float& dt) {
	updateMousePositions();
	updateInput(dt);
    updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target) {
	for (auto &it : buttons) {
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target) {
	if (!target) {
        target = window;
    }
	target->draw(background);
	renderButtons(*target);

}
