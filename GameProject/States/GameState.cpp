//
// Created by kevin on 22.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "GameState.h"


void GameState::initDeferredRender()
{
    this->renderTexture.create(
            this->stateData->graphSettings->resolution.width,
            this->stateData->graphSettings->resolution.height
    );

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(
            sf::IntRect(
                    0,
                    0,
                    this->stateData->graphSettings->resolution.width,
                    this->stateData->graphSettings->resolution.height
            )
    );
}

//Initializer functions
void GameState::initView()
{
    this->mainView.setSize(
            sf::Vector2f(
                    static_cast<float>(this->stateData->graphSettings->resolution.width),
                    static_cast<float>(this->stateData->graphSettings->resolution.height)
            )
    );

    this->mainView.setCenter(
            sf::Vector2f(
                    static_cast<float>(this->stateData->graphSettings->resolution.width) / 2.f,
                    static_cast<float>(this->stateData->graphSettings->resolution.height) / 2.f
            )
    );
}

void GameState::initKeyBinds()
{
    std::ifstream ifs("../Config/GameState_KeyBind.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            this->keyBinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void GameState::initFonts()
{
    if(!this->font.loadFromFile("../Fonts/Amatic-Bold.ttf")) {
        throw("ERROR - MainMenuState - Could not load");
    }
}

void GameState::initTextures() {
    if(!this->textures["PLAYER_SHEET"].loadFromFile("../Resources/Images/Sprites/Player/Idle3.png")) {
        throw "ERROR - GAMESTATE::InitTextures FAIL TO LOAD PLAYER_IDLE TEXTURE";
    }
}

void GameState::initPauseMenu() {
    this->pauseMenu = new PauseMenu(*this->window, this->font);
    this->pauseMenu->addButton("EXIT", 500.f, "Exit");
}

void GameState::initPlayers() {
    this->player = new Player(0,
                              0,
                              this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10,
                                "../Resources/Images/TextureGround/grassSheet.jpg");
    this->tileMap->loadFile("../Map/SaveMap.mp");
}

//Constructors / Destructors
GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->initDeferredRender();
    this->initView();
    this->initKeyBinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();

    this->initPlayers();
    this->initTileMap();
}

GameState::~GameState()
{
    delete this->pauseMenu;
    delete this->player;
    delete this->tileMap;
}

//Functions
void GameState::updateView(const float & dt)
{
    this->mainView.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

void GameState::updateInput(const float & dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime())
    {
        if (!this->pause)
            this->pauseState();
        else
            this->unpauseState();
    }
}

void GameState::updatePlayerInput(const float & dt)
{
    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);
}

void GameState::updatePauseMenuButtons()
{
    if (this->pauseMenu->isButtonPressed("QUIT"))
        this->endState();
}

void GameState::updateTileMap(const float & dt)
{
    this->tileMap->update();
    this->tileMap->collisionChecker(this->player, dt);
}

void GameState::update(const float& dt)
{
    this->updateMousePosition(&this->mainView);
    this->updateKeyTime(dt);
    this->updateInput(dt);

    if (!this->pause) //Unpaused update
    {
        this->updateView(dt);

        this->updatePlayerInput(dt);

        this->updateTileMap(dt);

        this->player->update(dt);
    }
    else //Paused update
    {
        this->pauseMenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    this->renderTexture.clear();

    this->renderTexture.setView(this->mainView);
    this->tileMap->render(this->renderTexture, this->player);

    this->player->render(this->renderTexture);

    if (this->pause) //Pause menu render
    {
        this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->pauseMenu->render(this->renderTexture);
    }

    //FINAL RENDER
    this->renderTexture.display();
    //this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
}