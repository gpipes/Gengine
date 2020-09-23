#include <iostream>
#include "gengine.hpp"
#include "guy.hpp"

int main(int, char**) {
	Gengine newGame("Test Game", 1600, 900);
	auto guy = std::make_shared<Guy>(newGame);
        newGame.loadSpriteComponents();
	newGame.run();
	return 0;
}
