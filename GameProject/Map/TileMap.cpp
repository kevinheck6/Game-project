//
// Created by kevin on 20.11.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "TileMap.h"


void TileMap::clearMemory()
{
    for (int x = 0; x < this->mapSizeGrid.x; x++)
    {
        for (int y = 0; y < this->mapSizeGrid.y; y++)
        {
            for (int z = 0; z < this->layers; z++)
            {
                delete this->map[x][y][z];
                this->map[x][y][z] = NULL;
            }
            this->map[x][y].clear();
        }
        this->map[x].clear();
    }
    this->map.clear();

    //std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
    this->gridSizeF = gridSize;
    this->gridSizeI = static_cast<int>(this->gridSizeF);
    this->mapSizeGrid.x = width;
    this->mapSizeGrid.y = height;
    this->mapSizeWoldF.x = static_cast<float>(width) * gridSize;
    this->mapSizeWoldF.y = static_cast<float>(height) * gridSize;
    this->layers = 1;
    this->textureFile = texture_file;

    this->fromX = 0;
    this->toX = 0;
    this->fromY = 0;
    this->toY = 0;
    this->layer = 0;

    this->map.resize(this->mapSizeGrid.x, std::vector< std::vector<Tile*> >());
    for (int x = 0; x < this->mapSizeGrid.x; x++)
    {
        for (int y = 0; y < this->mapSizeGrid.y; y++)
        {
            this->map[x].resize(this->mapSizeGrid.y, std::vector<Tile*>());

            for (int z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers, nullptr);
            }
        }
    }

    if (!this->tileTexture.loadFromFile(texture_file))
        std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";

    this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    this->collisionBox.setOutlineColor(sf::Color::Red);
    this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
    this->clearMemory();
}

//Accessors
const sf::Texture * TileMap::getTileTexture() const
{
    return &this->tileTexture;
}

//Functions
void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
    /* Take three indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it. */

    if (x < this->mapSizeGrid.x && x >= 0 &&
        y < this->mapSizeGrid.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        if (this->map[x][y][z] == nullptr)
        {
            /* OK To add tile. */
            this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTexture, texture_rect, collision, type);
            std::cout << "DEGBUG: ADDED TILE!" << "\n";
        }
    }
}

void TileMap::removeTile(const int x, const int y, const int z)
{
    /* Take three indicies from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it. */

    if (x < this->mapSizeGrid.x && x >= 0 &&
        y < this->mapSizeGrid.y && y >= 0 &&
        z < this->layers && z >= 0)
    {
        if (this->map[x][y][z] != nullptr)
        {
            /* OK To remove tile. */
            delete this->map[x][y][z];
            this->map[x][y][z] = nullptr;
            std::cout << "DEGBUG: REMOVED TILE!" << "\n";
        }
    }
}

void TileMap::saveFile(const std::string file_name)
{
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

    if (out_file.is_open())
    {
        out_file << this->mapSizeGrid.x << " " << this->mapSizeGrid.y << "\n"
                 << this->gridSizeI << "\n"
                 << this->layers << "\n"
                 << this->textureFile << "\n";

        for (int x = 0; x < this->mapSizeGrid.x; x++)
        {
            for (int y = 0; y < this->mapSizeGrid.y; y++)
            {
                for (int z = 0; z < this->layers; z++)
                {
                    if(this->map[x][y][z])
                        out_file << x << " " << y << " " << z << " " <<
                                 this->map[x][y][z]->getString()
                                 << " "; //MAKE SURE THIS LAST SPACE IS NOT SAVED!!!!
                }
            }
        }
    }
    else
    {
        std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
    }

    out_file.close();
}

void TileMap::loadFile(const std::string file_name)
{
    std::ifstream in_file;

    in_file.open(file_name);

    if (in_file.is_open())
    {
        sf::Vector2i size;
        int gridSize = 0;
        int layers = 0;
        std::string texture_file = "";
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
        this->gridSizeF = static_cast<float>(gridSize);
        this->gridSizeI = gridSize;
        this->mapSizeGrid.x = size.x;
        this->mapSizeGrid.y = size.y;
        this->layers = layers;
        this->textureFile = texture_file;

        this->clearMemory();

        this->map.resize(this->mapSizeGrid.x, std::vector< std::vector<Tile*> >());
        for (int x = 0; x < this->mapSizeGrid.x; x++)
        {
            for (int y = 0; y < this->mapSizeGrid.y; y++)
            {
                this->map[x].resize(this->mapSizeGrid.y, std::vector<Tile*>());

                for (int z = 0; z < this->layers; z++)
                {
                    this->map[x][y].resize(this->layers, NULL);
                }
            }
        }

        if (!this->tileTexture.loadFromFile(texture_file))
            std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << "\n";

        //Load all tiles
        while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
        {
            this->map[x][y][z] = new Tile(
                    x, y,
                    this->gridSizeF,
                    this->tileTexture,
                    sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
                    collision,
                    type
            );
        }
    }
    else
    {
        std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
    }

    in_file.close();
}

void TileMap::collisionChecker(Entity * entity, const float& dt)
{
    //WORLD BOUNDS
    if (entity->getPosition().x < 0.f)
    {
        entity->setPosition(0.f, entity->getPosition().y);
        entity->noVelocityX();
    }
    else if (entity->getPosition().x + entity->getGlobalBounds().width > this->mapSizeWoldF.x)
    {
        entity->setPosition(this->mapSizeWoldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
        entity->noVelocityX();
    }
    if (entity->getPosition().y < 0.f)
    {
        entity->setPosition(entity->getPosition().x, 0.f);
        entity->noVelocityY();
    }
    else if (entity->getPosition().y + entity->getGlobalBounds().height > this->mapSizeWoldF.y)
    {
        entity->setPosition(entity->getPosition().x, this->mapSizeWoldF.y - entity->getGlobalBounds().height);
        entity->noVelocityY();
    }

    //TILES
    this->layer = 0;

    this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
    if (this->fromX < 0)
        this->fromX = 0;
    else if (this->fromX > this->mapSizeGrid.x)
        this->fromX = this->mapSizeGrid.x;

    this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
    if (this->toX < 0)
        this->toX = 0;
    else if (this->toX > this->mapSizeGrid.x)
        this->toX = this->mapSizeGrid.x;

    this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
    if (this->fromY < 0)
        this->fromY = 0;
    else if (this->fromY > this->mapSizeGrid.y)
        this->fromY = this->mapSizeGrid.y;

    this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
    if (this->toY < 0)
        this->toY = 0;
    else if (this->toY > this->mapSizeGrid.y)
        this->toY = this->mapSizeGrid.y;

    for (int x = this->fromX; x < this->toX; x++)
    {
        for (int y = this->fromY; y < this->toY; y++)
        {
            sf::FloatRect playerBounds = entity->getGlobalBounds();
            sf::FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
            sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

            if (this->map[x][y][this->layer]->getCollision() &&
                this->map[x][y][this->layer]->intersects(nextPositionBounds)
                    )
            {
                //Bottom collision
                if (playerBounds.top < wallBounds.top
                    && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                    && playerBounds.left < wallBounds.left + wallBounds.width
                    && playerBounds.left + playerBounds.width > wallBounds.left
                        )
                {
                    entity->noVelocityY();
                    entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
                }

                    //Top collision
                else if (playerBounds.top > wallBounds.top
                         && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                         && playerBounds.left < wallBounds.left + wallBounds.width
                         && playerBounds.left + playerBounds.width > wallBounds.left
                        )
                {
                    entity->noVelocityY();
                    entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
                }

                //Right collision
                if (playerBounds.left < wallBounds.left
                    && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                    && playerBounds.top < wallBounds.top + wallBounds.height
                    && playerBounds.top + playerBounds.height > wallBounds.top
                        )
                {
                    entity->noVelocityX();
                    entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
                }

                    //Left collision
                else if (playerBounds.left > wallBounds.left
                         && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                         && playerBounds.top < wallBounds.top + wallBounds.height
                         && playerBounds.top + playerBounds.height > wallBounds.top
                        )
                {
                    entity->noVelocityX();
                    entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
                }
            }
        }
    }
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget & target, Entity* entity)
{
    if (entity)
    {
        this->layer = 0;

        this->fromX = entity->getGridPosition(this->gridSizeI).x - 5;
        if (this->fromX < 0)
            this->fromX = 0;
        else if (this->fromX > this->mapSizeGrid.x)
            this->fromX = this->mapSizeGrid.x;

        this->toX = entity->getGridPosition(this->gridSizeI).x + 8;
        if (this->toX < 0)
            this->toX = 0;
        else if (this->toX > this->mapSizeGrid.x)
            this->toX = this->mapSizeGrid.x;

        this->fromY = entity->getGridPosition(this->gridSizeI).y - 5;
        if (this->fromY < 0)
            this->fromY = 0;
        else if (this->fromY > this->mapSizeGrid.y)
            this->fromY = this->mapSizeGrid.y;

        this->toY = entity->getGridPosition(this->gridSizeI).y + 8;
        if (this->toY < 0)
            this->toY = 0;
        else if (this->toY > this->mapSizeGrid.y)
            this->toY = this->mapSizeGrid.y;

        for (int x = this->fromX; x < this->toX; x++)
        {
            for (int y = this->fromY; y < this->toY; y++)
            {
                this->map[x][y][this->layer]->render(target);
                if (this->map[x][y][this->layer]->getCollision())
                {
                    this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
                    target.draw(this->collisionBox);
                }
            }
        }
    }
    else
    {
        for (auto &x : this->map)
        {
            for (auto &y : x)
            {
                for (auto *z : y)
                {
                    if (z != NULL)
                    {
                        z->render(target);
                        if (z->getCollision())
                        {
                            this->collisionBox.setPosition(z->getPosition());
                            target.draw(this->collisionBox);
                        }
                    }
                }
            }
        }
    }
}