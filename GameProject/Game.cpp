#include "Game.h"

//Private functions

void Game::initVariable() {
    this->window = nullptr;

    //Game logic
}

void Game::initWindow() {
    //create SFML window using options from a window.ini file
    this->window = new sf::RenderWindow(sf::VideoMode(600, 800),"Game Project",
                                        sf::Style::Titlebar | sf::Style::Close);

}

//Constructor
Game::Game() {
    this->initWindow();
}

//Destructor
Game::~Game() {
    delete this->window;
}

void Game::updateDT() {
    //update the dt variable with the time to take it to render and update one frame
    this->dt = this->dtClock.getElapsedTime().asSeconds();
}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

void Game::update() {
    this->updateSFMLEvents();
}


void Game::render() {
    /*Return void
    render the game objects
    1) Render game object
    2) clear old frame
    3) display frames in window
    */

    //clear old frame
    this->window->clear();

    //draw game objects
    this->window->display();

}

void Game::run() {
    while (this->window->isOpen()) {
        this->updateDT();
        this->update();
        this->render();
    }
}





















