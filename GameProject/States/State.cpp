//
// Created by kevin on 22.10.2021.
//
#include "../Head Files/PreCompiledHeaders.h"
#include "State.h"

State::State(StateData* state_data) {
    this->stateData = state_data;
    this->window = state_data->window;
    this->supportedKeys = state_data->supportedKeys;
    this->states = state_data->states;
    this->quit = false;
    this->pause = false;
    this->keyTime = 0.f;
    this->keyTimeMax = 10.f;
    this->gridSize = state_data->gridSize;

}

State::~State() {

}

//Accessors
const bool &State::getQuit() const {
    return this->quit;
}

const bool State::getKeyTime() {
    if(this->keyTime >= this->keyTimeMax) {
        this->keyTime = 0.f;
        return true;
    }
    return  false;
}

//Functions
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
    this->mousePosGrid = sf::Vector2u(
            static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
            static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize));
}

void State::updateKeyTime(const float& dt) {
    if(this->keyTime < this->keyTimeMax) {
        this->keyTime += 50.f * dt;
    }
}




