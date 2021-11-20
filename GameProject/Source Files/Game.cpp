#include "../Head Files/PreCompiledHeaders.h"
#include "../Head Files/Game.h"

//Initializer functions

void Game::initVariables() {
    this->window = nullptr;
    this->dt = 0.f;

    //Game logic
}

void Game::initGraphSettings() {
    this->graphSettings.loadFile("../Config/Graphics.ini");
}


void Game::initStates() {
    this->states.push(new MainMenuState(this->window, this->graphSettings,
                                        &this->supportedKeys, &this->states));
}

void Game::initWindow() {
    //create SFML window using options from a window.ini file

    if(this->graphSettings.fullScreen) {
        this->window = new sf::RenderWindow(this->graphSettings.resolution,
                                            this->graphSettings.title,
                                            sf::Style::Fullscreen,
                                            this->graphSettings.contextSettings);
    } else {
        this->window = new sf::RenderWindow(this->graphSettings.resolution,
                                            this->graphSettings.title,
                                            sf::Style::Titlebar | sf::Style::Close,
                                            this->graphSettings.contextSettings);

    }
    this->window->setFramerateLimit(this->graphSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->graphSettings.verticalSync);

}

void Game::initKeys() {
    std::ifstream ifs("../Config/Supported_keys.ini");
    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }
    ifs.close();

    //DEBUG

    for (auto i :this->supportedKeys) {
        std::cout << i.first << " " << i.second << "\n";
    }

}

//Constructor/Destructor
Game::Game() {
    this->initVariables();
    this->initGraphSettings();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game() {
    delete this->window;
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

//  Functions

//Regular
void Game::endApplication() {
    std::cout << "ending Application" << "\n";

}
//Updates
void Game::updateDT() {
    //update the dt variable with the time to take it to render and update one frame
    this->dt = this->dtClock.restart().asSeconds();
    
}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

void Game::update()  {
    this->updateSFMLEvents();

    if(!this->states.empty()) {
        this->states.top()->update(this->dt);
        if(this->states.top()->getQuit()) {
            //Here will be things to do before quitting the game like save, animations
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    } else {
        this->endApplication();
        this->window->close();
    }

    //Aplication end


}

//Render
void Game::render() {
    /*Return void
    render the game objects
    1) Render game object
    2) clear old frame
    3) display frames in window
    */

    //clear old frame
    this->window->clear();

    //Render items
    if(!this->states.empty()) {
        this->states.top()->render();
    }

    //draw game objects
    this->window->display();

}


//Core
void Game::run() {
    while (this->window->isOpen()) {
        this->updateDT();
        this->update();
        this->render();
    }
}




