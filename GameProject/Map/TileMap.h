#pragma once

#include "../Tile/Tile.h"
#include "../Entities/Entity.h"

class Tile;
class Entity;

class TileMap {
private:
	void clear();

	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	int layers;
	std::vector< std::vector< std::vector< std::vector<Tile*> > > > map;
	std::stack<Tile*> deferredRenderStack;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

public:
	TileMap(float gridSize, int width, int height, const std::string& texture_file);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;
	int getLayerSize(int x, int y, int layerL) const;

	//Functions
	void addTile(int x, int y, int z, const sf::IntRect& texture_rect,
                 const bool& collision, const short& type);
	void removeTile(int x, int y, int z);
	void saveToFile(const std::string& file_name);
	void loadFromFile(const std::string& file_name);

	void updateCollision(Entity* entity, const float& dt);

	void update();
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);
	void renderDeferred(sf::RenderTarget& target);
};
