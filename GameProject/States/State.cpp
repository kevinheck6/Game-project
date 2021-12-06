
#include "../States/State.h"

State::State(StateData* state_data) {
	this->DataForStates = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->quit = false;
	this->paused = false;
	this->timeKey = 0.f;
	this->timeKeyMax = 10.f;
	this->gridSize = state_data->gridSize;
}

State::~State() = default;

//Accessors
const bool & State::getQuit() const {
	return quit;
}

bool State::getTimeKey() {
	if (timeKey >= timeKeyMax) {
        timeKey = 0.f;
		return true;
	}
	return false;
}

//Functions
void State::endState() {
	quit = true;
}

void State::pauseState() {
	paused = true;
}

void State::unpauseState() {
	paused = false;
}

void State::updateMousePositions(sf::View* view) {

	this->mousePosWindow = sf::Mouse::getPosition(*window);

	if(view) {
        window->setView(*view);
    }

	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mousePosGrid = sf::Vector2i(
			static_cast<int>(mousePosView.x) / static_cast<int>(gridSize),
			static_cast<int>(mousePosView.y) / static_cast<int>(gridSize));
	window->setView(window->getDefaultView());
}

void State::updateKeytime(const float& dt) {
	if (timeKey < timeKeyMax) {
        timeKey += 50.f * dt;
    }
}
