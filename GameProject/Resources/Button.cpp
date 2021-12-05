#include "../Head Files/PreCompiledHeaders.h"
#include "../Resources/Button.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, const std::string& text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id) {

	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button() = default;

//Accessors
bool gui::Button::isPressed() const {
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}



//Functions
void gui::Button::update(const sf::Vector2i& mousePosWindow) {
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	}
}

void gui::Button::render(sf::RenderTarget& target) {
	target.draw(this->shape);
	target.draw(this->text);
}

//TEXTURE SELECTOR ===================================================
gui::TextureSelector::TextureSelector(float x, float y, float width, float height, 
	float gridSize, const sf::Texture* texture_sheet,
	sf::Font& font, const std::string& text)
	: keytimeMax(2.f), keytime(0.f) {

	this->gridSize = gridSize;
	active = false;
	hidden = false;
	float offset = 0;

	bounds.setSize(sf::Vector2f(width, height));
	bounds.setPosition(x + offset, y + 75);
	bounds.setFillColor(sf::Color(50, 50, 50, 100));
	bounds.setOutlineThickness(1.f);
	bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	sheet.setTexture(*texture_sheet);
	sheet.setPosition(x + offset, y + 75);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width) {
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height) {
		this->sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	selector.setPosition(x + offset, y);
	selector.setSize(sf::Vector2f(gridSize, gridSize));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::Red);

	textureRect.width = static_cast<int>(gridSize);
	textureRect.height = static_cast<int>(gridSize);

	hide_btn = new gui::Button(
		x, y, 50.f, 50.f,
		&font, text, 50,
        sf::Color(250, 250, 250, 250),
        sf::Color(255,255,0, 250),
        sf::Color(20, 20, 20, 50),

        sf::Color(70, 70, 70, 0),
        sf::Color(150, 150, 150, 0),
        sf::Color(150, 20, 20, 0));
}

gui::TextureSelector::~TextureSelector() {
	delete hide_btn;
}

//Accessors
const bool& gui::TextureSelector::getActive() const {
	return active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const {
	return textureRect;
}

bool gui::TextureSelector::getKeytime() {
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

//Functions
void gui::TextureSelector::updateKeytime(const float& dt) {
	if (keytime < keytimeMax)
		keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt) {
	updateKeytime(dt);
	hide_btn->update(mousePosWindow);

	if (hide_btn->isPressed() && getKeytime()) {
		if (hidden) {
            hidden = false;
        }
		else {
            hidden = true;
        }
	}

	if (!hidden) {
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
            active = true;
        }
		else {
            active = false;
        }

		if (active) {
			mousePosGrid.x = (mousePosWindow.x - static_cast<int>(bounds.getPosition().x)) /
                    static_cast<unsigned>(gridSize);
			mousePosGrid.y = (mousePosWindow.y - static_cast<int>(bounds.getPosition().y)) /
                    static_cast<unsigned>(gridSize);

			selector.setPosition(
				bounds.getPosition().x + static_cast<float>(mousePosGrid.x) * gridSize,
				bounds.getPosition().y + static_cast<float>(mousePosGrid.y) * gridSize
			);

			textureRect.left = static_cast<int>(selector.getPosition().x - bounds.getPosition().x);
			textureRect.top = static_cast<int>(selector.getPosition().y - bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target) {
	if (!hidden) {
		target.draw(bounds);
		target.draw(sheet);

		if (active) {
            target.draw(selector);
        }
	}
    hide_btn->render(target);
}
