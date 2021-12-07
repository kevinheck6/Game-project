#pragma once

#include "../States/State.h"
#include "../Resources/PauseMenu.h"
#include "../Map/TileMap.h"
#include "../Resources/Button.h"

class PauseMenu;
class Player;
class TileMap;

class GameState :
	public State {
private:
    //Variables
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
    sf::Text text;
    bool endGame = false;
    std::map<std::string, gui::Button*> buttons;
    sf::RectangleShape background;
    sf::Font font;
	PauseMenu* pauseMenu;
	Player* player;
	sf::Texture texture;
	TileMap* tileMap;

	//Functions
    void initBackground();
	void initDeferredRender();
	void initView();
	void initKeyBinds() override;
    void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();
    void initButtons();

public:
    //Constructor
	explicit GameState(StateData* state_data);
    //Destructor
	~GameState() override;

	//Functions
    //Update
    void updateEndgame(int endGame);
    void updateButtons();
	void updateView(const float& dt);
	void updateInput(const float& dt) override;
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt) override;

    //Render
    void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target) override;
};
