#include <iostream>
#include "gengine.hpp"
#include "guy.hpp"

int main(int, char**) {
	Gengine newGame("Test Game", 1600, 900);
	GameObjectList world;
	auto guy = std::make_shared<Guy>();
	world.push_back(guy);
	newGame.setAndLoadGameWorld(world);
	newGame.run();
	return 0;
}
