#pragma once

#include "../States/GameState.h"
#include "../States/EditorState.h"
#include "../Resources/Button.h"

class MainMenuState :
	public State {
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, gui::Button*> buttons;
    sf::Text text;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeyBinds() override;
	void initButtons();

public:
    //Constructor
	explicit MainMenuState(StateData* state_data);
    //Destructor
	~MainMenuState() override;

	//Functions
    //Update
	void updateInput(const float& dt) override;
	void updateButtons();
	void update(const float& dt) override;

    //Render
    void renderText(sf::RenderTarget& target);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target) override;
};
