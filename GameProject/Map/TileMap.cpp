#include "../Head Files/PreCompiledHeaders.h"
#include "../Map/TileMap.h"

void TileMap::clear() {
	for (int x = 0; x < maxSizeWorldGrid.x; x++) {
		for (int y = 0; y < maxSizeWorldGrid.y; y++) {
			for (int z = 0; z < layers; z++) {
				for (auto & k : map[x][y][z]) {
					delete k;
					k = nullptr;
				}
				map[x][y][z].clear();
			}
			map[x][y].clear();
		}
		map[x].clear();
	}
	map.clear();
}

TileMap::TileMap(float gridSize, int width, int height, const std::string& texture_file) {
	gridSizeF = gridSize;
	gridSizeI = static_cast<int>(gridSizeF);
	maxSizeWorldGrid.x = width;
	maxSizeWorldGrid.y = height;
	maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	layers = 1;
	textureFile = texture_file;

	fromX = 0;
	toX = 0;
	fromY = 0;
	toY = 0;
	layer = 0;

	map.resize(maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
	for (int x = 0; x < maxSizeWorldGrid.x; x++) {
		for (int y = 0; y < maxSizeWorldGrid.y; y++) {
			this->map[x].resize(maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

			for (int z = 0; z < layers; z++) {
				map[x][y].resize(layers, std::vector<Tile*>());
			}
		}
	}

	if (!tileSheet.loadFromFile(texture_file)) {
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";
    }

	collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	collisionBox.setFillColor(sf::Color(255, 0, 0, 0));

    //Good for when we are working in the editor to know the collisions
	//this->collisionBox.setOutlineColor(sf::Color::Red);
	//this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap() {
	clear();
}

//Accessors
const sf::Texture * TileMap::getTileSheet() const {
	return &this->tileSheet;
}

int TileMap::getLayerSize(const int x, const int y, const int layerL) const {
	if (x >= 0 && x < map.size()) {
		if (y >= 0 && y < map[x].size()) {
			if (layerL >= 0 && layerL < map[x][y].size()) {
				return static_cast<int>(map[x][y][layerL].size());
			}
		}
	}
	return -1;
}

//Functions
void TileMap::addTile(const int x, const int y, const int z,
                      const sf::IntRect& texture_rect,
                      const bool& collision,
                      const short& type) {

	/* If it's allowed, add a tile */
	if (x < maxSizeWorldGrid.x && x >= 0 &&
		y < maxSizeWorldGrid.y && y >= 0 &&
		z < layers && z >= 0) {
		map[x][y][z].push_back(new Tile(x, y,
                                        gridSizeF,
                                        tileSheet,
                                        texture_rect, collision, type));
		std::cout << "DEGBUG: ADDED TILE!" << "\n";	
	}
}

void TileMap::removeTile(const int x, const int y, const int z) {
    /* If it's allowed, add a tile */
	if (x < maxSizeWorldGrid.x && x >= 0 &&
		y < maxSizeWorldGrid.y && y >= 0 &&
		z < layers && z >= 0)
	{
		if (!map[x][y][z].empty()) {
			delete map[x][y][z][map[x][y][z].size()-1];
			map[x][y][z].pop_back();
			std::cout << "DEGBUG: REMOVED TILE!" << "\n";
		}
	}
}

void TileMap::saveToFile(const std::string& file_name) {
	/*Saves the entire tilemap to a text-file.
	Format: 
	Basic:
	Size x y
	gridSize
	layers
	texture file

	All tiles:
	gridPos x y layer 
	Texture rect x y 
	collision 
	type
	*/

	std::ofstream out_file;
	
	out_file.open(file_name);

	if (out_file.is_open()) {
		out_file << maxSizeWorldGrid.x << " " << maxSizeWorldGrid.y << "\n"
			<< gridSizeI << "\n"
			<< layers << "\n"
			<< textureFile << "\n";

		for (int x = 0; x < maxSizeWorldGrid.x; x++) {
			for (int y = 0; y < maxSizeWorldGrid.y; y++) {
				for (int z = 0; z < layers; z++) {
					if (!map[x][y][z].empty()) {
						for (size_t k = 0; k < map[x][y][z].size(); k++) {
							out_file << x << " " << y << " " << z << " " << map[x][y][z][k]->getAsString() << " ";
						}		
					}
				}
			}
		}
	} else {
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string& file_name) {
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open()) {
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file;
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		gridSizeF = static_cast<float>(gridSize);
		gridSizeI = gridSize;
		maxSizeWorldGrid.x = size.x;
		maxSizeWorldGrid.y = size.y;
		layers = layers;
		textureFile = texture_file;

		clear();

		map.resize(maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
		for (int i = 0; i < maxSizeWorldGrid.x; i++) {
			for (int j = 0; j < maxSizeWorldGrid.y; j++) {
				map[i].resize(maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());
				for (int k = 0; k < layers; k++) {
					map[i][j].resize(layers, std::vector<Tile*>());
				}
			}
		}

		if (!tileSheet.loadFromFile(texture_file)) {
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";
        }

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type) {
			map[x][y][z].push_back(new Tile(x, y,gridSizeF,
                                                  tileSheet,
                                                  sf::IntRect(trX, trY,
                                                              gridSizeI, gridSizeI),collision,
                                                              type));
		}
	} else {
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
}

void TileMap::updateCollision(Entity * entity, const float& dt) {
	//Bounds of the word size
	if (entity->getPosition().x < 0.f) {
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	} else if (entity->getPosition().x + entity->getGlobalBounds().width > maxSizeWorldF.x) {
		entity->setPosition(maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f) {
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	} else if (entity->getPosition().y + entity->getGlobalBounds().height > maxSizeWorldF.y) {
		entity->setPosition(entity->getPosition().x, maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//TILES
	layer = 0;

	fromX = entity->getGridPosition(gridSizeI).x - 1;
	if (fromX < 0) {
        fromX = 0;
    } else if (fromX > maxSizeWorldGrid.x) {
        fromX = maxSizeWorldGrid.x;
    }

	toX = entity->getGridPosition(gridSizeI).x + 3;
	if (toX < 0) {
        toX = 0;
    } else if (toX > maxSizeWorldGrid.x) {
        toX = maxSizeWorldGrid.x;
    }

	fromY = entity->getGridPosition(gridSizeI).y - 1;
	if (fromY < 0) {
        fromY = 0;
    } else if (fromY > maxSizeWorldGrid.y) {
        fromY = maxSizeWorldGrid.y;

    }

	toY = entity->getGridPosition(gridSizeI).y + 3;
	if (toY < 0) {
        toY = 0;
    } else if (toY > maxSizeWorldGrid.y)
		toY = maxSizeWorldGrid.y;

	for (int x = fromX; x < toX; x++) {
		for (int y = fromY; y < toY; y++) {
			for (auto & k : map[x][y][layer]) {
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = k->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (k->getCollision() && k->intersects(nextPositionBounds)) {
					//Bottom collision
					if (playerBounds.top < wallBounds.top &&
                        playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
                        playerBounds.left < wallBounds.left + wallBounds.width &&
                        playerBounds.left + playerBounds.width > wallBounds.left) {

						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                    }

					//Collision for top conner
					else if (playerBounds.top > wallBounds.top &&
                            playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
                            playerBounds.left < wallBounds.left + wallBounds.width &&
                            playerBounds.left + playerBounds.width > wallBounds.left) {

						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					//Collision for Right conner
					if (playerBounds.left < wallBounds.left &&
                        playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
                        playerBounds.top < wallBounds.top + wallBounds.height &&
                        playerBounds.top + playerBounds.height > wallBounds.top) {

						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

                    //Collision for Left conner
					else if (playerBounds.left > wallBounds.left &&
                            playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
                            playerBounds.top < wallBounds.top + wallBounds.height &&
                            playerBounds.top + playerBounds.height > wallBounds.top) {

						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget & target, const sf::Vector2i& gridPosition) {
	layer = 0;

	fromX = gridPosition.x - 8;
	if (fromX < 0) {
        fromX = 0;
    } else if (fromX > maxSizeWorldGrid.x)
		fromX = maxSizeWorldGrid.x;

	toX = gridPosition.x + 10;
	if (toX < 0) {
        toX = 0;
    } else if (toX > maxSizeWorldGrid.x) {
        toX = maxSizeWorldGrid.x;
    }

	fromY = gridPosition.y - 6;
	if (fromY < 0) {
        fromY = 0;
    }
	else if (fromY > maxSizeWorldGrid.y) {
        fromY = maxSizeWorldGrid.y;
    }

	toY = gridPosition.y + 5;
	if (toY < 0) {
        toY = 0;
    }
	else if (toY > maxSizeWorldGrid.y) {
        toY = maxSizeWorldGrid.y;
    }

	for (int x = fromX; x < toX; x++) {
		for (int y = fromY; y < toY; y++) {
			for (auto & k : map[x][y][layer]) {
				if (k->getType() == TileTypes::DOODAD) {
					deferredRenderStack.push(k);
				} else {
					k->render(target);
				}
				if (k->getCollision()) {
					collisionBox.setPosition(k->getPosition());
					target.draw(collisionBox);
				}
			}		
		}
	}	
}

void TileMap::renderDeferred(sf::RenderTarget & target) {
	while (!deferredRenderStack.empty()) {
		deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}
