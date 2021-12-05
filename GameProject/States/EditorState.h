#pragma once

#include "../States/State.h"
#include "../Resources/Button.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"

class TileMap;
class State;
class PauseMenu;


class EditorState :
	public State {
private:
	//Variables
	sf::View view;
	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu;
	std::map<std::string, gui::Button*> buttons;
	TileMap* tileMap;
	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	gui::TextureSelector* textureSelector;
	sf::IntRect textureRect;
	bool collision;
	short type;
	float cameraSpeed;
	int layer;

	//Functions
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds() override;
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

public:
	explicit EditorState(StateData* state_data);
	~EditorState() override;

	//Functions
	void updateInput(const float& dt) override;
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target) override;
};

