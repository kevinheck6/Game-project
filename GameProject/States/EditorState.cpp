#include "../Head Files/PreCompiledHeaders.h"
#include "../States/EditorState.h"

//Initializer functions
void EditorState::initVariables() {
	textureRect = sf::IntRect(0, 0,
                                    static_cast<int>(stateData->gridSize),
                                    static_cast<int>(stateData->gridSize));
	collision = false;
	type = TileTypes::DEFAULT;
	cameraSpeed = 200.f;
	layer = 0;
    this->textureSelector = nullptr;
}

void EditorState::initView() {
	view.setSize(sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)));

	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f);
}

void EditorState::initBackground() {}

void EditorState::initFonts() {
	if (!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
		throw("ERROR - EditorState was not able to load the font");
	}
}

void EditorState::initText() {
	cursorText.setFont(this->font);
	cursorText.setFillColor(sf::Color::White);
	cursorText.setCharacterSize(30);
	cursorText.setPosition(mousePosView.x, mousePosView.y);
}

void EditorState::initKeybinds() {

	std::ifstream ifs("../Config/EditorState_KeyBind.ini");

	if (ifs.is_open()) {
		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void EditorState::initPauseMenu() {
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 600.f, "Quit");
	this->pmenu->addButton("SAVE", 200.f, "Save");
	this->pmenu->addButton("LOAD", 400.f, "Load");
}

void EditorState::initButtons() {}

void EditorState::initGui() {
    //SIDEBAR
    sidebar.setPosition(0.f,0.f);
	sidebar.setSize(sf::Vector2f(static_cast<float>(stateData->gfxSettings->resolution.width),
            80.f));
	sidebar.setFillColor(sf::Color(50,50,50, 100));
	sidebar.setOutlineColor(sf::Color(sf::Color::White));
	sidebar.setOutlineThickness(1.f);

    //RECTANGLE - MAP
	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));

	selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	selectorRect.setOutlineThickness(2.f);
	selectorRect.setOutlineColor(sf::Color::Green);

	selectorRect.setTexture(tileMap->getTileSheet());
	selectorRect.setTextureRect(textureRect);

    //TEXTURE
	this->textureSelector = new gui::TextureSelector(
		10.f, 10.f,
        1100.f, 800.f,
		this->stateData->gridSize,
        this->tileMap->getTileSheet(),
		this->font,
        "Tiles");

}

void EditorState::initTileMap() {
	tileMap = new TileMap(stateData->gridSize,
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
	initKeybinds();
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

	delete pmenu;
	delete tileMap;
	delete textureSelector;
}

//Functions
void EditorState::updateInput(const float & dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		if (!this->paused) {
            this->pauseState();
        }
		else {
            this->unpauseState();
        }
	}
}

void EditorState::updateEditorInput(const float& dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_UP")))) {
		view.move(0.f, -cameraSpeed * dt);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_DOWN")))) {
		view.move(0.f, cameraSpeed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_LEFT")))) {
		view.move(-cameraSpeed * dt, 0.f);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_RIGHT")))) {
		view.move(cameraSpeed * dt, 0.f);
	}

	//Add a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeytime()) {
		if (!sidebar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow))) {
			if (!this->textureSelector->getActive()) {
				tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0,
                                 textureRect,
                                 this->collision,
                                 this->type);
			} else {
				textureRect = textureSelector->getTextureRect();
			}
		}
	}
	//Remove a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime()) {
		if (!sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {
			if (!textureSelector->getActive()) {
                tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
            }
		}
	}

	//Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_COLLISION")))
    && getKeytime()) {
		if (collision) {
            collision = false;
        } else {
            collision = true;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("INCREASE_TYPE")))
    && getKeytime()) {
		++type;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("DECREASE_TYPE")))
    && getKeytime()){
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
		selectorRect.setPosition(static_cast<float>(mousePosGrid.x) * stateData->gridSize,
                                 static_cast<float>(mousePosGrid.y) * stateData->gridSize);
	}

	cursorText.setPosition(this->mousePosView.x + 20.f, this->mousePosView.y - 50.f);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y <<
		"\n" << mousePosGrid.x << "    " << mousePosGrid.y <<
		"\n" << textureRect.left / 100 << " " << textureRect.top / 100 <<
		"\n" << "Collision: " << collision <<
		"\n" << "Type: " << type <<
		"\n" << "Tiles: " << tileMap->getLayerSize(mousePosGrid.x, mousePosGrid.y, layer);

	this->cursorText.setString(ss.str());
}

void EditorState::updatePauseMenuButtons() {
	if (pmenu->isButtonPressed("QUIT")) {
        endState();
    }
	if (pmenu->isButtonPressed("SAVE")) {
        tileMap->saveToFile("../Map/text.slmp");
    }


	if (pmenu->isButtonPressed("LOAD")) {
        tileMap->loadFromFile("../Map/text.slmp");
    }
}

void EditorState::update(const float& dt) {
	updateMousePositions(&view);
	updateKeytime(dt);
	updateInput(dt);

    //Not paused
	if (!paused){
		updateButtons();
		updateGui(dt);
		updateEditorInput(dt);
	} else { // Paused
		pmenu->update(this->mousePosWindow);
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
	target.draw(sidebar);

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
		pmenu->render(*target);
	}	
}