//
// Created by kevin on 29.10.2021.
//

#pragma once

class HitBoxComponent {
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitBox;
    sf::FloatRect futurePosition;
    float offsetX;
    float offsetY;
public:
    HitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    virtual ~HitBoxComponent();

    //Accessors
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
    //Modifiers
    void setPosition(const sf::Vector2f& position);
    void setPosition(const float x, const float y);
    //Functions
    bool intersects(const sf::FloatRect& fRect);

    void update();
    void render(sf::RenderTarget& target);

};

