#include "../Head Files/PreCompiledHeaders.h"
#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(sf::Sprite& sprite,
                                 float offset_x, float offset_y,
                                 float width, float height)
	: sprite(sprite), offSetForX(offset_x), offSetForY(offset_y) {
    futurePos.left = 0.f;
    futurePos.top = 0.f;
    futurePos.width = width;
    futurePos.height = height;

	hitBox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
	hitBox.setSize(sf::Vector2f(width, height));
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineThickness(-1.f);
	hitBox.setOutlineColor(sf::Color::Green);

}

HitBoxComponent::~HitBoxComponent() = default;

//Accessors
const sf::Vector2f & HitBoxComponent::getPosition() const {
	return hitBox.getPosition();
}

sf::FloatRect HitBoxComponent::getGlobalBounds() const {
	return hitBox.getGlobalBounds();
}

const sf::FloatRect & HitBoxComponent::getFuturePosition(const sf::Vector2f & velocity) {
    futurePos.left = hitBox.getPosition().x + velocity.x;
    futurePos.top = hitBox.getPosition().y + velocity.y;

	return futurePos;
}

//Modifiers
void HitBoxComponent::setPosition(const sf::Vector2f& position) {
	hitBox.setPosition(position);
	sprite.setPosition(position.x - offSetForX, position.y - offSetForY);
}

void HitBoxComponent::setPosition(const float x, const float y) {
	hitBox.setPosition(x, y);
	sprite.setPosition(x - offSetForX, y - offSetForY);
}

//Functions
void HitBoxComponent::update() {
	hitBox.setPosition(sprite.getPosition().x + offSetForX, sprite.getPosition().y + offSetForY);
}

void HitBoxComponent::render(sf::RenderTarget & target) {
	target.draw(hitBox);
}
