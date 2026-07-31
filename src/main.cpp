#include "gam/game.h"
#include <iostream>

int main() {
    std::cout << "Starting game..." << std::endl;
    gmr::Game game;
    std::cout << "Game created, running..." << std::endl;
    game.run();
    std::cout << "Game finished" << std::endl;
    return 0;
}
