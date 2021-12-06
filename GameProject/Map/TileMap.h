#pragma once

#include "../Tile/Tile.h"
#include "../Entities/Entity.h"

class Tile;
class Entity;

class TileMap {
private:
	void memoryClear();

    //Variables
	float gridSizeFloat;
	int gridSizeInt;
	sf::Vector2i SizeWorldGrid;
	sf::Vector2f SizeWorldF;
	int layers;
	std::vector< std::vector< std::vector< std::vector<Tile*> > > > map;
	std::stack<Tile*> deferredRenderStack;
	std::string fileTexture;
	sf::Texture tileTexture;
	sf::RectangleShape boxCollision;
    bool endGame = false;
	int startX;
	int endX;
	int startY;
	int endY;
	int layer;

public:
    //Constructor
	TileMap(float gridSize, int width, int height, const std::string& texture_file);

    //Destructor
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;
	int getLayerSize(int x, int y, int layerL) const;

	//Functions
    //Tiles
	void addTile(int x, int y, int z, const sf::IntRect& texture_rect,
                 const bool& collision, const short& type);
	void removeTile(int x, int y, int z);

    //Save and load
	void saveToFile(const std::string& file_name);
	void loadFromFile(const std::string& file_name);

    //Update
    bool updateEndGame() const;
	void updateCollision(Entity* entity, const float& dt);
    void updateType(Entity* entity, const float& dt);
	void update();

    //Render
	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);
	void renderDeferred(sf::RenderTarget& target);
};
