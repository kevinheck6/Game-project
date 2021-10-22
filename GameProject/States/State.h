#pragma once

#include "../Entities/Entity.h"

class State {
private:

protected:
    sf::RenderWindow* window;
    std::map<std::string,int>* supportedKeys;
    std::map<std::string,int> keyBinds;
    bool quit;

    //Resources
    std::vector<sf::Texture> textures;

    //Functions
    virtual void initKeyBinds() = 0;

public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
    virtual ~State();

    const bool& getQuit() const;

    virtual void checkForQuit();
    virtual void endState() = 0;

    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


