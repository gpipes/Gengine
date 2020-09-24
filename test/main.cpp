#include <iostream>
#include "gengine.hpp"
#include "guy.hpp"

int main(int, char**) {
	Gengine newGame("Test Game", 1600, 900);
	newGame.registerSystem(std::make_shared<System>(guyRunningSystem),
		{ std::type_index(typeid(Sprite)),
		 std::type_index(typeid(GuyRunning)) });
	for (int i = 0; i < 1; ++i) {
		auto guy = std::make_shared<Guy>(newGame, Position(i, i));
	}
	newGame.loadSpriteComponents();
	newGame.run();
	return 0;
}
