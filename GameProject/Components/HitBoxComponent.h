#pragma once

class HitBoxComponent {
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitBox;
	sf::FloatRect futurePos;
	float offSetForX;
	float offSetForY;

public:
    //Constructor
	HitBoxComponent(sf::Sprite& sprite,
                    float offset_x, float offset_y,
                    float width, float height);
    //Destructor
	virtual ~HitBoxComponent();

	//Accessors
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getFuturePosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(float x, float y);

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};
