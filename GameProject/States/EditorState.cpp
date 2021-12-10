#include "../Head Files/PreCompiledHeaders.h"
#include "../States/EditorState.h"

//Initializer functions
void EditorState::initVariables() {
	textureRect = sf::IntRect(0, 0,
                                    static_cast<int>(DataForStates->gridSize),
                                    static_cast<int>(DataForStates->gridSize));
    collisionToggle = false;
	type = TileTypes::DEFAULT;
    speedOfCamera = 200.f;
	layer = 0;
    this->textureSelector = nullptr;
}

void EditorState::initView() {
	view.setSize(sf::Vector2f(
			static_cast<float>(this->DataForStates->graphicsSettings->resolution.width),
			static_cast<float>(this->DataForStates->graphicsSettings->resolution.height)));

	this->view.setCenter(
            static_cast<float>(this->DataForStates->graphicsSettings->resolution.width) / 2.f,
            static_cast<float>(this->DataForStates->graphicsSettings->resolution.height) / 2.f);
}

void EditorState::initBackground() {}

void EditorState::initFonts() {
	if (!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
		throw("ERROR - EditorState was not able to load the font");
	}
}

void EditorState::initText() {
	cursorText.setFont(font);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setCharacterSize(30);
	cursorText.setPosition(mousePosView.x, mousePosView.y);
}

void EditorState::initKeyBinds() {

	std::ifstream ifs("../Config/EditorState_Keys.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void EditorState::initPauseMenu() {
    pauseMenu = new PauseMenu(*window, font);

	pauseMenu->addButton("EXIT", 600.f, "Quit");
	pauseMenu->addButton("SAVE", 200.f, "Save");
	pauseMenu->addButton("LOAD", 400.f, "Load");
}

void EditorState::initButtons() {}

void EditorState::initGui() {
    //Show the SideBar in the Screen
    sideBarEditor.setPosition(0.f, 0.f);
	sideBarEditor.setSize(sf::Vector2f(static_cast<float>(DataForStates->graphicsSettings->resolution.width),
                                       80.f));
	sideBarEditor.setFillColor(sf::Color(50, 50, 50, 100));
	sideBarEditor.setOutlineColor(sf::Color(sf::Color::White));
	sideBarEditor.setOutlineThickness(1.f);

    //Show the Rectangle in the map
	selectorRect.setSize(sf::Vector2f(DataForStates->gridSize, DataForStates->gridSize));

	selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	selectorRect.setOutlineThickness(2.f);
	selectorRect.setOutlineColor(sf::Color::Green);

	selectorRect.setTexture(tileMap->getTileSheet());
	selectorRect.setTextureRect(textureRect);

    //Show all the textures to choose
	this->textureSelector = new gui::TextureSelector(
		10.f, 10.f,
        1100.f, 800.f,
		this->DataForStates->gridSize,
        this->tileMap->getTileSheet(),
		this->font,
        "Tiles");

}

void EditorState::initTileMap() {
	tileMap = new TileMap(DataForStates->gridSize,
                          300, 300,
                          "../Resources/Images/TextureGround/forest.png");
}

EditorState::EditorState(StateData* state_data)
	: State(state_data) {
	initVariables();
	initView();
	initBackground();
	initFonts();
	initText();
    initKeyBinds();
	initPauseMenu();
	initButtons();
	initTileMap();
	initGui();
}

EditorState::~EditorState() {
	auto it = buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

	delete pauseMenu;
	delete tileMap;
	delete textureSelector;
}

//Functions
void EditorState::updateInput(const float & dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("EXIT")))
    && this->getTimeKey()) {
		if (!this->paused) {
            this->pauseState();
        }
		else {
            this->unpauseState();
        }
	}
}

void EditorState::updateEditorInput(const float& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CAMERA_UP")))) {
		view.move(0.f, -speedOfCamera * dt);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CAMERA_DOWN")))) {
		view.move(0.f, speedOfCamera * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CAMERA_LEFT")))) {
		view.move(-speedOfCamera * dt, 0.f);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CAMERA_RIGHT")))) {
		view.move(speedOfCamera * dt, 0.f);
	}

	//Add a tile to the tile-map
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getTimeKey()) {
		if (!sideBarEditor.getGlobalBounds().contains(sf::Vector2f(mousePosWindow))) {
			if (!this->textureSelector->getActive()) {
				tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0,
                                 textureRect,
                                 this->collisionToggle,
                                 this->type);
			} else {
				textureRect = textureSelector->getTextureRect();
			}
		}
	}
	//Remove a tile from the tile-map
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getTimeKey()) {
		if (!sideBarEditor.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {
			if (!textureSelector->getActive()) {
                tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
            }
		}
	}

	//Toggle collisionToggle
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("COLLISION")))
        && getTimeKey()) {
		if (collisionToggle) {
            collisionToggle = false;
        } else {
            collisionToggle = true;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("UP_TYPE")))
               && getTimeKey()) {
		++type;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("DOWN_TYPE")))
               && getTimeKey()){
		if(type > 0) {
            --type;
        }
	}
}

void EditorState::updateButtons() {
	for (auto &it : buttons) {
		it.second->update(mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt) {
	textureSelector->update(this->mousePosWindow, dt);
	
	if (!textureSelector->getActive()) {
		selectorRect.setTextureRect(textureRect);
		selectorRect.setPosition(static_cast<float>(mousePosGrid.x) * DataForStates->gridSize,
                                 static_cast<float>(mousePosGrid.y) * DataForStates->gridSize);
	}

	cursorText.setPosition(this->mousePosView.x + 20.f, this->mousePosView.y - 50.f);
	std::stringstream ss;
	ss <<"\n" << "Collision: " << collisionToggle <<
        "\n" << "Type: " << type <<
		"\n" << "Tiles: " << tileMap->getLayerSize(mousePosGrid.x, mousePosGrid.y, layer);

	this->cursorText.setString(ss.str());
}

void EditorState::updatePauseMenuButtons() {
	if (pauseMenu->ButtonPressed("EXIT")) {
        endState();
    }
	if (pauseMenu->ButtonPressed("SAVE")) {
        tileMap->saveToFile("../Map/text.slmp");
    }
	if (pauseMenu->ButtonPressed("LOAD")) {
        tileMap->loadFromFile("../Map/text.slmp");
    }
}

void EditorState::update(const float& dt) {
	updateMousePositions(&view);
    updateTimeKey(dt);
	updateInput(dt);

    //Not paused
	if (!paused){
		updateButtons();
		updateGui(dt);
		updateEditorInput(dt);
	} else { // Paused
		pauseMenu->update(this->mousePosWindow);
		updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target) {
	for (auto &it : buttons) {
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target) {
	if (!textureSelector->getActive()) {
		target.setView(view);
		target.draw(selectorRect);
	}

	target.setView(window->getDefaultView());
	textureSelector->render(target);
	target.draw(sideBarEditor);

	target.setView(view);
	target.draw(cursorText);
}

void EditorState::render(sf::RenderTarget* target) {
	if (!target) {
        target = window;
    }

	target->setView(view);
	tileMap->render(*target, mousePosGrid);
	tileMap->renderDeferred(*target);

	target->setView(window->getDefaultView());
	renderButtons(*target);
	renderGui(*target);

	if (paused) {
		target->setView(window->getDefaultView());
		pauseMenu->render(*target);
	}	
}