#include <iostream>
#include <cstdlib>
#include "gengine.hpp"
#include "guy.hpp"

int main(int, char**) {
    Gengine newGame("Test Game", 1920, 1080, false);
    newGame.registerSystem(guyRunningSystem,
                           { std::type_index(typeid(Sprite)),
                             std::type_index(typeid(GuyRunning)),
                             std::type_index(typeid(Position))});
    for (int i = 0; i < 100000; ++i) {
        Guy(newGame, Position(std::rand() % 3120 - 30,
                              std::rand() % 2280 - 40));
        //auto guy = std::make_shared<Guy>(newGame, Position(i, i));
    }
    newGame.loadSpriteComponents();
    newGame.run();
    return 0;
}
