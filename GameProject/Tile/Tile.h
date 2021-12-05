#pragma once

// It will e the type of tile, each one will have different interactions
enum TileTypes {DEFAULT = 0, ENDGAME = 1, DOODAD};

class Tile {
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	//Accessors
	const short& getType() const;

	//Functions
	const bool & getCollision() const;
	const sf::Vector2f& getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	bool intersects(sf::FloatRect bounds) const;
	std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& target);
};
