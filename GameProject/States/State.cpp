//
// Created by kevin on 22.10.2021.
//

#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) {
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->states = states;
    this->quit = false;
    this->pause = false;

}

State::~State() {

}

const bool &State::getQuit() const {
    return this->quit;
}



void State::endState() {
    this->quit = true;
}

void State::pauseState() {
    this->pause = true;
}

void State::unpauseState() {
    this->pause = false;
}

void State::updateMousePosition() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}


