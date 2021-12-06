#include "../Head Files/PreCompiledHeaders.h"
#include "../Map/TileMap.h"

void TileMap::memoryClear() {
	for (int x = 0; x < SizeWorldGrid.x; x++) {
		for (int y = 0; y < SizeWorldGrid.y; y++) {
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
    gridSizeFloat = gridSize;
    gridSizeInt = static_cast<int>(gridSizeFloat);
    SizeWorldGrid.x = width;
    SizeWorldGrid.y = height;
    SizeWorldF.x = static_cast<float>(width) * gridSize;
    SizeWorldF.y = static_cast<float>(height) * gridSize;
	layers = 1;
    fileTexture = texture_file;

    startX = 0;
    endX = 0;
    startY = 0;
    endY = 0;
	layer = 0;

	map.resize(SizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
	for (int x = 0; x < SizeWorldGrid.x; x++) {
		for (int y = 0; y < SizeWorldGrid.y; y++) {
			this->map[x].resize(SizeWorldGrid.y, std::vector< std::vector<Tile*> >());

			for (int z = 0; z < layers; z++) {
				map[x][y].resize(layers, std::vector<Tile*>());
			}
		}
	}

	if (!tileTexture.loadFromFile(texture_file)) {
        std::cout << "ERROR - TileMap.cpp - Fail in load tileTexture - Name of File: " << texture_file << "\n";
    }

	boxCollision.setSize(sf::Vector2f(gridSize, gridSize));
	boxCollision.setFillColor(sf::Color(255, 0, 0, 0));

    //Good for when we are working in the editor to know the collisions
	//this->boxCollision.setOutlineColor(sf::Color::Red);
	//this->boxCollision.setOutlineThickness(1.f);
}

TileMap::~TileMap() {
    memoryClear();
}

//Accessors
const sf::Texture * TileMap::getTileSheet() const {
	return &this->tileTexture;
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
	if (x < SizeWorldGrid.x && x >= 0 &&
        y < SizeWorldGrid.y && y >= 0 &&
		z < layers && z >= 0) {
		map[x][y][z].push_back(new Tile(x, y,
                                        gridSizeFloat,
                                        tileTexture,
                                        texture_rect, collision, type));
	}
}

void TileMap::removeTile(const int x, const int y, const int z) {
    /* If it's allowed, add a tile */
	if (x < SizeWorldGrid.x && x >= 0 &&
        y < SizeWorldGrid.y && y >= 0 &&
		z < layers && z >= 0)
	{
		if (!map[x][y][z].empty()) {
			delete map[x][y][z][map[x][y][z].size()-1];
			map[x][y][z].pop_back();
		}
	}
}

void TileMap::saveToFile(const std::string& file_name) {
	std::ofstream out_file;
	
	out_file.open(file_name);

	if (out_file.is_open()) {
		out_file << SizeWorldGrid.x << " " << SizeWorldGrid.y << "\n"
                 << gridSizeInt << "\n"
                 << layers << "\n"
                 << fileTexture << "\n";

		for (int x = 0; x < SizeWorldGrid.x; x++) {
			for (int y = 0; y < SizeWorldGrid.y; y++) {
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
		std::cout << "ERROR - TileMap.cpp - Was not able to Save File - File name: " <<
        file_name << "\n";
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

		//General information
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles information
		gridSizeFloat = static_cast<float>(gridSize);
        gridSizeInt = gridSize;
        SizeWorldGrid.x = size.x;
        SizeWorldGrid.y = size.y;
		layers = layers;
        fileTexture = texture_file;

        memoryClear();

		map.resize(SizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
		for (int i = 0; i < SizeWorldGrid.x; i++) {
			for (int j = 0; j < SizeWorldGrid.y; j++) {
				map[i].resize(SizeWorldGrid.y, std::vector< std::vector<Tile*> >());
				for (int k = 0; k < layers; k++) {
					map[i][j].resize(layers, std::vector<Tile*>());
				}
			}
		}

		if (!tileTexture.loadFromFile(texture_file)) {
            std::cout << "ERROR - TileMap.cpp - Problem at load tileTexture - File Name: " <<
            texture_file << "\n";
        }

		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type) {
			map[x][y][z].push_back(new Tile(x, y, gridSizeFloat,
                                            tileTexture,
                                            sf::IntRect(trX, trY,
                                                        gridSizeInt, gridSizeInt), collision,
                                            type));
		}
	} else {
		std::cout << "ERROR - TileMap.cpp - Problem at load from tileTexture - File Name: " <<
        file_name << "\n";
	}

	in_file.close();
}

bool TileMap::updateEndGame() const {
    return this->endGame;
}

void TileMap::updateCollision(Entity * entity, const float& dt) {
	//Bounds of the word size
	if (entity->getPosition().x < 0.f) {
		entity->setPosition(0.f, entity->getPosition().y);
        entity->makeNullVelocityX();
	} else if (entity->getPosition().x + entity->getGlobalBounds().width > SizeWorldF.x) {
		entity->setPosition(SizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->makeNullVelocityX();
	}
	if (entity->getPosition().y < 0.f) {
		entity->setPosition(entity->getPosition().x, 0.f);
        entity->makeNullVelocityY();
	} else if (entity->getPosition().y + entity->getGlobalBounds().height > SizeWorldF.y) {
		entity->setPosition(entity->getPosition().x, SizeWorldF.y - entity->getGlobalBounds().height);
        entity->makeNullVelocityY();
	}

	//Tile Bounds
	layer = 0;

    startX = entity->getGridPosition(gridSizeInt).x - 1;
	if (startX < 0) {
        startX = 0;
    } else if (startX > SizeWorldGrid.x) {
        startX = SizeWorldGrid.x;
    }

    endX = entity->getGridPosition(gridSizeInt).x + 3;
	if (endX < 0) {
        endX = 0;
    } else if (endX > SizeWorldGrid.x) {
        endX = SizeWorldGrid.x;
    }

    startY = entity->getGridPosition(gridSizeInt).y - 1;
	if (startY < 0) {
        startY = 0;
    } else if (startY > SizeWorldGrid.y) {
        startY = SizeWorldGrid.y;

    }

    endY = entity->getGridPosition(gridSizeInt).y + 3;
	if (endY < 0) {
        endY = 0;
    } else if (endY > SizeWorldGrid.y)
        endY = SizeWorldGrid.y;

	for (int x = startX; x < endX; x++) {
		for (int y = startY; y < endY; y++) {
			for (auto & k : map[x][y][layer]) {
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = k->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getFuturePositionBounds(dt);

				if (k->getCollision() && k->intersects(nextPositionBounds)) {
					//Bottom collisionTile
					if (playerBounds.top < wallBounds.top &&
                        playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
                        playerBounds.left < wallBounds.left + wallBounds.width &&
                        playerBounds.left + playerBounds.width > wallBounds.left) {

                        entity->makeNullVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                    }

					//Collision for top conner
					else if (playerBounds.top > wallBounds.top &&
                            playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
                            playerBounds.left < wallBounds.left + wallBounds.width &&
                            playerBounds.left + playerBounds.width > wallBounds.left) {

                        entity->makeNullVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					//Collision for Right conner
					if (playerBounds.left < wallBounds.left &&
                        playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
                        playerBounds.top < wallBounds.top + wallBounds.height &&
                        playerBounds.top + playerBounds.height > wallBounds.top) {

                        entity->makeNullVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

                    //Collision for Left conner
					else if (playerBounds.left > wallBounds.left &&
                            playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
                            playerBounds.top < wallBounds.top + wallBounds.height &&
                            playerBounds.top + playerBounds.height > wallBounds.top) {

                        entity->makeNullVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}
}

void TileMap::updateType(Entity *entity, const float &dt) {
    for (int x = startX; x < endX; x++) {
        for (int y = startY; y < endY; y++) {
            for (auto & k : map[x][y][layer]) {
                sf::FloatRect playerBounds = entity->getGlobalBounds();
                sf::FloatRect wallBounds = k->getGlobalBounds();
                sf::FloatRect nextPositionBounds = entity->getFuturePositionBounds(dt);

                if ((k->getType() == 1) && k->intersects(nextPositionBounds)) {
                    //Bottom collisionTile
                    if (playerBounds.top < wallBounds.top &&
                        playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
                        playerBounds.left < wallBounds.left + wallBounds.width &&
                        playerBounds.left + playerBounds.width > wallBounds.left) {

                        endGame = true;
                    }

                        //Collision for top conner
                    else if (playerBounds.top > wallBounds.top &&
                             playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
                             playerBounds.left < wallBounds.left + wallBounds.width &&
                             playerBounds.left + playerBounds.width > wallBounds.left) {

                        endGame = true;
                    }

                    //Collision for Right conner
                    if (playerBounds.left < wallBounds.left &&
                        playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
                        playerBounds.top < wallBounds.top + wallBounds.height &&
                        playerBounds.top + playerBounds.height > wallBounds.top) {

                        endGame = true;
                    }

                        //Collision for Left conner
                    else if (playerBounds.left > wallBounds.left &&
                             playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
                             playerBounds.top < wallBounds.top + wallBounds.height &&
                             playerBounds.top + playerBounds.height > wallBounds.top) {

                        endGame = true;
                    }
                }
            }
        }
    }
}

void TileMap::update() {}

void TileMap::render(sf::RenderTarget & target, const sf::Vector2i& gridPosition) {
	layer = 0;

    //Set up how many tiles will be show in the screen
    startX = gridPosition.x - 4;
	if (startX < 0) {
        startX = 0;
    } else if (startX > SizeWorldGrid.x)
        startX = SizeWorldGrid.x;

    endX = gridPosition.x + 4;
	if (endX < 0) {
        endX = 0;
    } else if (endX > SizeWorldGrid.x) {
        endX = SizeWorldGrid.x;
    }

    startY = gridPosition.y - 4;
	if (startY < 0) {
        startY = 0;
    } else if (startY > SizeWorldGrid.y) {
        startY = SizeWorldGrid.y;
    }

    endY = gridPosition.y + 3;
	if (endY < 0) {
        endY = 0;
    } else if (endY > SizeWorldGrid.y) {
        endY = SizeWorldGrid.y;
    }

	for (int x = startX; x < endX; x++) {
		for (int y = startY; y < endY; y++) {
			for (auto & k : map[x][y][layer]) {
				if (k->getType() == TileTypes::DOODAD) {
					deferredRenderStack.push(k);
				} else {
					k->render(target);
				}
				if (k->getCollision()) {
					boxCollision.setPosition(k->getPosition());
					target.draw(boxCollision);
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




