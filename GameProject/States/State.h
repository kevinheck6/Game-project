#pragma once

#include "../Entities/Player.h"
#include "../Resources/GraphicsSettings.h"

class Player;
class GraphSettings;
class State;

class StateData {
public:
    StateData() {};

    //Variables
    float gridSize;
    sf::RenderWindow* window;
    GraphSettings* graphSettings;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;
};

class State {
private:

protected:
    StateData* stateData;
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string,int>* supportedKeys;
    std::map<std::string,int> keyBinds;
    bool quit;
    bool pause;
    float keyTime;
    float keyTimeMax;
    float gridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    //Resources
    std::map<std::string ,sf::Texture> textures;

    //Functions
    virtual void initKeyBinds() = 0;

public:
    State(StateData* state_data);
    virtual ~State();

    //Accessors
    const bool& getQuit() const;
    const bool getKeyTime();
    //Functions

    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePosition();
    virtual void updateKeyTime(const float& dt);
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


