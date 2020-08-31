#include <iostream>
#include "gengine.hpp"
#include "gameobjectbase.hpp"

namespace {
	static const double msPerFrame60FPS = 16.667;
}

Gengine::Gengine(std::string name, int width, int height) 
	: _screenMan(name, width, height),
	_msPerFrame(msPerFrame60FPS)
{
	SDL_Init(0);
	_screenMan.init();
}

Gengine::~Gengine() {
	SDL_Quit();
}

void Gengine::run() {
	bool isRunning = true;
	int startFrameTime = 0, endFrameTime = 0, frameDelta = 0;

	while (isRunning) {
		startFrameTime = SDL_GetTicks();
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				isRunning = false;
				continue;
			}
		}

                _screenMan.drawWorld(_gameWorld);

		endFrameTime = SDL_GetTicks();
		frameDelta = endFrameTime - startFrameTime;
		if (frameDelta < _msPerFrame) {
			SDL_Delay(static_cast<Uint32>(_msPerFrame - frameDelta));
		}
	}
}

void Gengine::setAndLoadGameWorld(std::vector<std::shared_ptr<GameObjectBase>> world) {
	setGameWorld(world);
	loadGameWorld();
}

void Gengine::setGameWorld(std::vector<std::shared_ptr<GameObjectBase>> world) {
	_gameWorld = world;
}

// load all game objects in the world onto the screen we have
void Gengine::loadGameWorld() {
	for (auto gameObject : _gameWorld) {
		_screenMan.load(*gameObject);
	}
}

