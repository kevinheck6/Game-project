//
// Created by kevin on 22.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "Button.h"

gui::Button::Button(float x, float y, float width, float height,
               sf::Font* font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color, sf::Color outline_hover_color,sf::Color outline_active_color,
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
    this->text.setPosition( // Centered Text
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y
            );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idlerColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->outlineIdlerColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;
    this->outlineActiveColor = outline_active_color;
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

const std::string gui::Button::getText() const{
    return this->text.getString();
}

const short unsigned &gui::Button::getId() const {
    return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text) {
    this->text.setString(text);
}

void gui::Button::setId(const unsigned short id) {
    this->id = id;
}
//Functions
void gui::Button::update(const sf::Vector2i& mousePosWindow) {
    //update the booleans for hover and pressed

    //IDLE
    this->buttonState = BTN_IDLE;

    //Hover
    if(this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))){
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
            this->shape.setOutlineColor(this->outlineIdlerColor);
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

        default:
            this->shape.setFillColor(sf::Color::Red);
            this->text.setFillColor(sf::Color::Blue);
            this->shape.setOutlineColor(sf::Color::White);
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


    this->activeElement = new gui::Button(
            x, y, width, height,
            &this->font,list[default_index], 25,
            sf::Color(250, 70, 70, 150), sf::Color(250, 250, 250, 200), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
            sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

    for (int i = 0; i < numberElements; ++i) {
        this->list.push_back(
                new gui::Button(
                        x, (y + ((i+1) * height)), width, height,
                        &this->font,list[i], 25,
                        sf::Color(250, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
                        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200),sf::Color(150, 20, 20, 200),
                        sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0))
        );
    }
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

const unsigned short &gui::DropDownList::getActiveElementId() const {
    return this->activeElement->getId();
}

//Functions

void gui::DropDownList::updateKeyTime(const float& dt) {
    if(this->keyTime < this->keyTimeMax) {
        this->keyTime += 10.f * dt;
    }
}

void gui::DropDownList::update(const sf::Vector2i &mousePosWindow, const float& dt) {
    this->updateKeyTime(dt);
    this->activeElement->update(mousePosWindow);
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
            i->update(mousePosWindow);

            if(i->isPressed() && this->getKeyTime()) {
                this->showList = false;
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
            }
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


//TextureSelector PART..........................................

gui::TextureSelector::TextureSelector(float x, float y, float width, float height,
                                      float gridSize, const sf::Texture* texture_sheet,
                                      sf::Font& font, std::string text)
        : keyTimeMax(2.f), keyTime(0.f)
{
    this->gridSize = gridSize;
    this->active = false;
    this->hidden = false;
    float offset = 100.f;

    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(x + offset, y);
    this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    this->texture.setTexture(*texture_sheet);
    this->texture.setPosition(x + offset, y);

    if (this->texture.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
    {
        this->texture.setTextureRect(sf::IntRect(0, 0,
                                                 static_cast<int>(this->bounds.getGlobalBounds().width),
                                                 static_cast<int>(this->texture.getGlobalBounds().height)));
    }
    if (this->texture.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
    {
        this->texture.setTextureRect(sf::IntRect(0, 0,
                                                 static_cast<int>(this->texture.getGlobalBounds().width),
                                                 static_cast<int>(this->bounds.getGlobalBounds().height)));
    }

    this->selector.setPosition(x + offset, y);
    this->selector.setSize(sf::Vector2f(gridSize, gridSize));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Red);

    this->textureRectangle.width = static_cast<int>(gridSize);
    this->textureRectangle.height = static_cast<int>(gridSize);

    this->hide_button = new gui::Button(
            y, x, 50.f, 50.f,
            &font, text, 16,
            sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
            sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
    );
}

gui::TextureSelector::~TextureSelector()
{
    delete this->hide_button;
}

//Accessors
const bool& gui::TextureSelector::getActive() const
{
    return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
    return this->textureRectangle;
}

const bool gui::TextureSelector::getKeyTime()
{
    if (this->keyTime >= this->keyTimeMax)
    {
        this->keyTime = 0.f;
        return true;
    }

    return false;
}

//Functions
void gui::TextureSelector::updateKeyTime(const float& dt)
{
    if (this->keyTime < this->keyTimeMax)
        this->keyTime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
    this->updateKeyTime(dt);
    this->hide_button->update(mousePosWindow);

    if (this->hide_button->isPressed() && this->getKeyTime())
    {
        if (this->hidden)
            this->hidden = false;
        else
            this->hidden = true;
    }

    if (!this->hidden)
    {
        if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
            this->active = true;
        else
            this->active = false;

        if (this->active)
        {
            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

            this->selector.setPosition(
                    this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                    this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
            );

            //Update texture rectangle
            this->textureRectangle.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
            this->textureRectangle.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
        }
    }
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
    if (!this->hidden)
    {
        target.draw(this->bounds);
        target.draw(this->texture);

        if (this->active)
            target.draw(this->selector);
    }

    this->hide_button->render(target);
}