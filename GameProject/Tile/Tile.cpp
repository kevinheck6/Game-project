#include "../Head Files/PreCompiledHeaders.h"
#include "../Tile/Tile.h"

Tile::Tile() {
	collision = false;
	type = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool collision, short type) {
	shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	shape.setTexture(&texture);
	shape.setTextureRect(texture_rect);

    this->collision = collision;

    this->type = type;
}

Tile::~Tile() = default;

//Accessors
const short & Tile::getType() const {
	return type;
}

const bool & Tile::getCollision() const {
	return collision;
}

const sf::Vector2f & Tile::getPosition() const {
	return shape.getPosition();
}

sf::FloatRect Tile::getGlobalBounds() const {
	return shape.getGlobalBounds();
}

//Functions
bool Tile::intersects(const sf::FloatRect bounds) const {
	return shape.getGlobalBounds().intersects(bounds);
}

std::string Tile::getAsString() const {
	std::stringstream ss;
	ss <<
    shape.getTextureRect().left << " " <<
    shape.getTextureRect().top << " " <<
    collision << " " <<
    type;

	return ss.str();
}

void Tile::update() {}

void Tile::render(sf::RenderTarget & target) {
	target.draw(shape);
}
