#include <iostream>
#include <cstdlib>
#include "gengine.hpp"
#include "guy.hpp"

int main(int, char**) {
    Gengine newGame("Test Game", 1920, 1080, false);
    newGame.registerSystem(std::make_shared<System>(guyRunningSystem),
                           { std::type_index(typeid(Sprite)),
                             std::type_index(typeid(GuyRunning)) });
    for (int i = 0; i < 10000; ++i) {
        auto guy = std::make_shared<Guy>(newGame, Position(std::rand() % 1920 - 160,
                                                           std::rand() % 1080 - 200));
        //auto guy = std::make_shared<Guy>(newGame, Position(i, i));
    }
    newGame.loadSpriteComponents();
    newGame.run();
    return 0;
}
