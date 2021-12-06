#pragma once
#include "../Entities/Entity.h"

class Entity;

class Player :
	public Entity {
private:
	//Variables
	bool isAttacking;

	//Initializer
	void initVariables();

public:
    //Constructor
	Player(float x, float y, sf::Texture& texture_sheet);
    //Destructor
	~Player() override;

	//Functions
	void updateAttack();
	void updateAnimation(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget& target) override;
};

