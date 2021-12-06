#pragma once

#include "../Entities/Player.h"
#include "../Resources/GraphicsSettings.h"

class State;
class Player;
class GraphicsSettings;

class StateData {
public:
	StateData() {};

	//Variables
	float gridSize{};
	sf::RenderWindow* window{};
	GraphicsSettings* graphicsSettings{};
	std::map<std::string, int>* supportedKeys{};
	std::stack<State*>* states{};
};

class State {
private:

protected:
    //Variables
	StateData* DataForStates;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	bool quit;
	bool paused;
	float timeKey;
	float timeKeyMax;
	float gridSize;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeyBinds() = 0;

public:
    //Constructor
	State(StateData* state_data);
    //Destructor
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	bool getTimeKey();

	//Functions	
	void endState(); 
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions(sf::View* view = nullptr);
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};
