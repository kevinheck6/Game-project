#include <iostream>
#include "Game.h"


int main() {
    //initialize random seed
    std::srand(static_cast<unsigned>(time(nullptr)));

    //initialize game engine;
    Game game;

//Game loop
    while (game.running() && !game.getEndGame()) {
        //Update
    game.update();
        // Render
    game.render();
        //Draw game
    }

    return 0;
}
