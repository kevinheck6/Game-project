//
// Created by kevin on 22.10.2021.
//

#include "Button.h"

gui::Button::Button(float x, float y, float width, float height,
               sf::Font* font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color) {

    this->buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_color);


    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition( // Centered Text
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
            );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idlerColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

}

gui::Button::~Button() {

}

//Accessors
const bool gui::Button::isPressed() const {
    if(this->buttonState == BTN_ACTIVE) {
        return true;
    } else {
        return false;
    }
}

const std::string& gui::Button::getText() const{
    return this->text.getString();
}

//Modifiers
void gui::Button::setText(const std::string text) {
    this->text.setString(text);
}

//Functions
void gui::Button::update(const sf::Vector2f& mousePos) {
    //update the booleans for hover and pressed

    //IDLE
    this->buttonState = BTN_IDLE;

    //Hover
    if(this->shape.getGlobalBounds().contains(mousePos)){
        this->buttonState = BTN_HOVER;

        //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState) {
        case BTN_IDLE:
            this->shape.setFillColor(this->idlerColor);
            this->text.setFillColor(this->textIdleColor);
            break;

        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            this->text.setFillColor(this->textHoverColor);
            break;

        case BTN_ACTIVE:
            this->shape.setFillColor(this->activeColor);
            this->text.setFillColor(this->textActiveColor);
            break;

        default:
            this->shape.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::Blue);
            break;

    }
}

void gui::Button::render(sf::RenderTarget& target) {
    target.draw(this->shape);
    target.draw(this->text);
}


//DropDownList PART..........................................

gui::DropDownList::DropDownList(float x, float y, float width, float height,
                                sf::Font& font, std::string list[], unsigned numberElements, unsigned default_index)
    : font(font), showList(false), keyTimeMax(2.f), keyTime(0.f) {

    //unsigned numberElements = (sizeof(list) / sizeof(std::string));

    for (int i = 0; i < numberElements; ++i) {
        this->list.push_back(
                new gui::Button(
                        x, (y + (i * height)), width, height,
                        &this->font,list[i], 25,
                        sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(150, 20, 20, 200))
        );
    }

    this->activeElement = new Button(*this->list[default_index]);
}

gui::DropDownList::~DropDownList() {
    delete this->activeElement;
    for (int i = 0; i < this->list.size(); ++i) {
        delete this->list[i];
    }
}

//Accessories
const bool gui::DropDownList::getKeyTime() {
    if(this->keyTime >= keyTimeMax) {
        this->keyTime = 0.f;
        return true;
    }
    return false;
}

//Functions
void gui::DropDownList::updateKeyTime(const float& dt) {
    if(this->keyTime < this->keyTimeMax) {
        this->keyTime += 10.f * dt;
    }
}

void gui::DropDownList::update(const sf::Vector2f &mousePos, const float& dt) {
    this->updateKeyTime(dt);
    this->activeElement->update(mousePos);
    //Show and hide the list of options
    if(this->activeElement->isPressed() && this->getKeyTime()) {
        if(this->showList) {
            this->showList = false;
        } else {
            this->showList = true;
        }
    }
    if(this->showList) {
        for (auto &i : this->list) {
            i->update(mousePos);
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget &target) {
    this->activeElement->render(target);
    if(this->showList) {
        for (auto &i : this->list) {
            i->render(target);
        }
    }
}






