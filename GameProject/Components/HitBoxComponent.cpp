#include "../Head Files/PreCompiledHeaders.h"
#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(sf::Sprite& sprite,
                                 float offset_x, float offset_y,
                                 float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y) {
	nextPosition.left = 0.f;
	nextPosition.top = 0.f;
	nextPosition.width = width;
	nextPosition.height = height;

	hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(-1.f);
	hitbox.setOutlineColor(sf::Color::Green);

}

HitBoxComponent::~HitBoxComponent() = default;

//Accessors
const sf::Vector2f & HitBoxComponent::getPosition() const {
	return hitbox.getPosition();
}

sf::FloatRect HitBoxComponent::getGlobalBounds() const {
	return hitbox.getGlobalBounds();
}

const sf::FloatRect & HitBoxComponent::getNextPosition(const sf::Vector2f & velocity) {
	nextPosition.left = hitbox.getPosition().x + velocity.x;
	nextPosition.top = hitbox.getPosition().y + velocity.y;

	return nextPosition;
}

//Modifiers
void HitBoxComponent::setPosition(const sf::Vector2f& position) {
	hitbox.setPosition(position);
	sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void HitBoxComponent::setPosition(const float x, const float y) {
	hitbox.setPosition(x, y);
	sprite.setPosition(x - offsetX, y - offsetY);
}

//Functions
bool HitBoxComponent::intersects(const sf::FloatRect& frect) {
	return hitbox.getGlobalBounds().intersects(frect);
}

void HitBoxComponent::update() {
	hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitBoxComponent::render(sf::RenderTarget & target) {
	target.draw(hitbox);
}
