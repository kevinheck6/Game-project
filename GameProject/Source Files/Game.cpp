#include "../Head Files/PreCompiledHeaders.h"
#include "../Head Files/Game.h"

//Static functions

//Initializer functions
void Game::initVariables()
{
    this->window = NULL;

    this->dt = 0.f;

    this->gridSize = 100.f;
}

void Game::initGraphSettings()
{
    this->graphSettings.loadFile("../Config/Graphics.ini");
}

void Game::initWindow()
{
    /*Creates a SFML window.*/

    if(this->graphSettings.fullScreen)
        this->window = new sf::RenderWindow(
                this->graphSettings.resolution,
                this->graphSettings.title,
                sf::Style::Fullscreen,
                this->graphSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(
                this->graphSettings.resolution,
                this->graphSettings.title,
                sf::Style::Titlebar | sf::Style::Close,
                this->graphSettings.contextSettings);

    this->window->setFramerateLimit(this->graphSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->graphSettings.verticalSync);
}

void Game::initKeys()
{
    std::ifstream ifs("../Config/Supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
        {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();

//DEBUG REMOVE LATER!
    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.graphSettings = &this->graphSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
}

//Constructors/Destructors
Game::Game()
{
    this->initVariables();
    this->initGraphSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//Functions
void Game::endApplication()
{
    std::cout << "Ending Application!" << "\n";
}

void Game::updateDT()
{
    /*Updates the dt variable with the time it takes to update and render one frame.*/

    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        if (this->window->hasFocus())
        {
            this->states.top()->update(this->dt);

            if (this->states.top()->getQuit())
            {
                this->states.top()->endState();
                delete this->states.top();
                this->states.pop();
            }
        }
    }
        //Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    //Render items
    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDT();
        this->update();
        this->render();
    }
}
