#pragma once

#include "../States/GameState.h"
#include "../States/EditorState.h"
#include "../States/SettingsState.h"
#include "../Resources/Button.h"

class MainMenuState :
	public State {
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, gui::Button*> buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds() override;
	void initButtons();

public:
	explicit MainMenuState(StateData* state_data);
	~MainMenuState() override;

	//Functions
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target) override;
};
