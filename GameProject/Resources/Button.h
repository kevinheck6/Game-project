//
// Created by kevin on 22.10.2021.
//
#pragma once

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {
    class Button {
    private:
        short unsigned buttonState;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idlerColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineIdlerColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;


    public:
        Button(float x, float y, float width, float height,
               sf::Font* font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Transparent,
               sf::Color outline_hover_color= sf::Color::Transparent,
               sf::Color outline_active_color= sf::Color::Transparent,
               short unsigned id = 0);
        ~Button();

        //Accessors
        const bool isPressed() const;
        const std::string getText() const;
        const short unsigned& getId() const;

        //Modifiers
        void setText(const std::string text);
        void setId(const short unsigned id);

        //Functions
        void update(const sf::Vector2i& mousePosWindow);
        void render(sf::RenderTarget& target);


    };

    class DropDownList {

    private:
        float keyTime;
        float keyTimeMax;
        sf::Font& font;
        gui::Button* activeElement;
        std::vector<gui::Button*> list;
        bool showList;
    public:
        //Constructors
        DropDownList(float x, float y, float width, float height,
                     sf::Font& font, std::string list[], unsigned numberElements,unsigned default_index = 0);
        ~DropDownList();

        //Accessories
        const bool getKeyTime();
        const unsigned short& getActiveElementId() const;

        //Functions
        void updateKeyTime(const float& dt);
        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget& target);
    };

    class TextureSelector {
    private:
        //Variables
        float keyTime;
        const float keyTimeMax;

        float gridSize;
        bool active;
        bool hidden;
        gui::Button* hide_button;
        sf::RectangleShape bounds;
        sf::Sprite texture;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRectangle;

    public:

        TextureSelector(float x, float y, float width, float height, float gridSize,
                        const sf::Texture* texture_sheet, sf::Font& font, std::string text);
        ~TextureSelector();

        //Accessors
        const bool getKeyTime();
        const bool& getActive() const;
        const sf::IntRect& getTextureRect() const;

        //Functions
        void updateKeyTime(const float& dt);
        void update(const sf::Vector2i& mousePosWindow, const float& dt);
        void render(sf::RenderTarget& target);

    };
}



