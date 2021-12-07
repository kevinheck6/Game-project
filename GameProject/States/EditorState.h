#pragma once

#include "../States/State.h"
#include "../Resources/Button.h"
#include "../Resources/PauseMenu.h"
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
	PauseMenu* pauseMenu;
	std::map<std::string, gui::Button*> buttons;
	TileMap* tileMap;
	sf::RectangleShape sideBarEditor;
	sf::RectangleShape selectorRect;
	gui::TextureSelector* textureSelector;
	sf::IntRect textureRect;
	bool collisionTile;
	short type;
	float speedOfCamera;
	int layer;

	//Functions
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeyBinds() override;
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

public:
    //Constructor
	explicit EditorState(StateData* state_data);

    //Destructor
	~EditorState() override;

	//Functions
    //Update
	void updateInput(const float& dt) override;
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt) override;

    //Render
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target) override;
};

