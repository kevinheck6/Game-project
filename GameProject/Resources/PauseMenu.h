#pragma once

#include "../Head Files/PreCompiledHeaders.h"
#include"Button.h"

class PauseMenu {
private:
    //Variables
	sf::Font& font;
	sf::Text textInMenu;
	sf::RectangleShape background;
	sf::RectangleShape SquareMenu;
	std::map<std::string, gui::Button*> buttons;

public:
    //Constructor
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
    //Destructor
	virtual ~PauseMenu();

	//Functions
	bool ButtonPressed(const std::string& key);
	void addButton(const std::string& key, float y, const std::string& text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};

