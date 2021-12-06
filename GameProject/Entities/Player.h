#pragma once
#include "../Entities/Entity.h"

class Entity;

class Player :
	public Entity {
public:
    //Constructor
	Player(float x, float y, sf::Texture& texture_sheet);
    //Destructor
	~Player() override;

	//Functions
    //Update
	void updateAnimation(const float& dt);
	void update(const float& dt) override;

    //Render
	void render(sf::RenderTarget& target) override;
};

