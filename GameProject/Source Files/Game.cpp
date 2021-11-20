#include "../Head Files/Game.h"

//Initializer functions

void Game::initVariables() {
    this->window = nullptr;
    this->fullscreen = false;
    this->dt = 0.f;

    //Game logic
}

void Game::initStates() {
    this->states.push(new MainMenuState(this->window,&this->supportedKeys, &this->states));
}

void Game::initWindow() {
    //create SFML window using options from a window.ini file

    std::ifstream ifs("../Config/Window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 90;
    bool vertical_sync_enable = false;
    unsigned antialiasing_level = 0;

    if(ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enable;
        ifs >> antialiasing_level;
    }
    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if(this->fullscreen) {
        this->window = new sf::RenderWindow(window_bounds,title,sf::Style::Fullscreen, windowSettings);
    } else {
        this->window = new sf::RenderWindow(window_bounds,title, sf::Style::Titlebar | sf::Style::Close,
                                            windowSettings);

    }
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enable);


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
























