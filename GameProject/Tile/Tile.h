//
// Created by kevin on 13.11.2021.
//
#pragma once

enum TileTypes {DEFAULT = 0};

class Tile {
private:
protected:
    sf::RectangleShape tile;
    bool collision;
    short type; // Maybe will have to be only short type

public:
    Tile();
    Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& rectangle_texture,
         bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    //Accessors
    const bool& getCollision() const;
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const bool intersects(const sf::FloatRect bounds) const;
    const std::string getString() const;



    //Functions


    void update();
    void render(sf::RenderTarget& target);

};


