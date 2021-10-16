#include <iostream>
#include "Game.h"


int main() {
    //initialize random seed
    std::srand(static_cast<unsigned>(time(nullptr)));

    //initialize game engine;
    Game game;

    game.run();
    return 0;
}
