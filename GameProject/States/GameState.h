#pragma once

#include "../States/State.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"

class PauseMenu;
class Player;
class TileMap;

class GameState :
	public State {
private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;

	Player* player;
	sf::Texture texture;
	
	TileMap* tileMap;

	//Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();

public:
	explicit GameState(StateData* state_data);
	~GameState() override;

	//Functions
	void updateView(const float& dt);
	void updateInput(const float& dt) override;
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
};
