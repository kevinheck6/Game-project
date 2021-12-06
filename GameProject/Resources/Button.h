#pragma once

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {
	class Button {
	private:
        //Variables
		short unsigned buttonState;

		sf::RectangleShape RectangleShape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
        //Constructor
		Button(float x, float y, float width, float height,
			sf::Font* font, const std::string& text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent,
            sf::Color outline_hover_color = sf::Color::Transparent,
            sf::Color outline_active_color = sf::Color::Transparent);
        //Destructor
		~Button();

		//Accessors
		bool isPressed() const;

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
	};


	class TextureSelector {
	private:
		float timeKey;
		const float timeKeyMax;
		float gridSize;
		bool active;
		bool hidden;
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
        //Constructor
		TextureSelector(float x, float y, float width, float height, 
			float gridSize, const sf::Texture* texture_sheet, 
			sf::Font& font, const std::string& text);

        //Destructor
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		//Functions
        //Time
		bool getTimeKey();

        //Update
		void updateTimeKey(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);

        //Render
		void render(sf::RenderTarget& target);
	};
}
