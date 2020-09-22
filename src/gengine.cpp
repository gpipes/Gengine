#include <iostream>
#include "gengine.hpp"
#include "gameobjectbase.hpp"

namespace {
    static const double msPerFrame60FPS = 16.667;
}

Gengine::Gengine(std::string name, int width, int height) 
    : _screenMan(name, width, height),
      _componentMan(),
      _systemMan(std::make_shared<SystemManager>(_componentMan))
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
    int totalFrameTime = 0;

    while (isRunning) {
        startFrameTime = SDL_GetTicks();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            _inputMan.addInputEvent(e);
        }

        if (_inputMan.isQuit()) {
            isRunning = false;
            continue;
        }

        _systemMan->tick();
        _updateMan.updateWorld(_gameWorld, _inputMan);
        _screenMan.drawWorld(_gameWorld);
        _inputMan.clearInputEvents();

        endFrameTime = SDL_GetTicks();
        frameDelta = endFrameTime - startFrameTime;
        if (frameDelta < msPerFrame60FPS) {
            SDL_Delay(static_cast<Uint32>(msPerFrame60FPS - frameDelta));
        }
    }
}

void Gengine::setAndLoadGameWorld(GameObjectList world) {
    setGameWorld(world);
    loadGameWorld();
}

void Gengine::setGameWorld(GameObjectList world) {
    _gameWorld = world;
}

// load all game objects in the world onto the screen we have
void Gengine::loadGameWorld() {
    for (auto gameObject : _gameWorld) {
        _screenMan.load(*gameObject);
    }
}

