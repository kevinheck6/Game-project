#include "../Head Files/PreCompiledHeaders.h"
#include "../Resources/PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font) {
	//Initialize the background
	background.setSize(
		sf::Vector2f(static_cast<float>(window.getSize().x),static_cast<float>(window.getSize().y)));
	background.setFillColor(sf::Color(20, 20, 20, 100));

	//Initialize the SquareMenu
	SquareMenu.setSize(sf::Vector2f(
            static_cast<float>(window.getSize().x) / 4.f,
            static_cast<float>(window.getSize().y) - 100.f));
	SquareMenu.setFillColor(sf::Color(20, 20, 20, 200));
	SquareMenu.setPosition(static_cast<float>(window.getSize().x) / 2.f - SquareMenu.getSize().x / 2.f, 30.f);

	//Initialize the text
	textInMenu.setFont(font);
	textInMenu.setFillColor(sf::Color(255, 255, 255, 200));
	textInMenu.setCharacterSize(60);
	textInMenu.setString("PAUSED");
	textInMenu.setPosition(
            SquareMenu.getPosition().x + SquareMenu.getSize().x / 2.f - textInMenu.getGlobalBounds().width / 2.f,
            SquareMenu.getPosition().y + 40.f);

}

PauseMenu::~PauseMenu() {
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it) {
		delete it->second;
	}
}

//Functions
bool PauseMenu::ButtonPressed(const std::string& key) {
	return buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string& key, float y, const std::string& text) {
	float width = 250.f;
	float height = 65.f;
	float x = SquareMenu.getPosition().x + SquareMenu.getSize().x / 2.f - width / 2.f;

	buttons[key] = new gui::Button(
		x, y, width, height,
		&font, text, 50,
		sf::Color(70, 70, 70, 200),
        sf::Color(250, 250, 250, 250),
        sf::Color(20, 20, 20, 50),

		sf::Color(70, 70, 70, 0),
        sf::Color(150, 150, 150, 0),
        sf::Color(20, 20, 20, 0)
	);
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow) {
	for (auto &i : buttons) {
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::render(sf::RenderTarget & target) {
	target.draw(background);
	target.draw(SquareMenu);

	for (auto &i : buttons) {
		i.second->render(target);
	}

	target.draw(textInMenu);
}