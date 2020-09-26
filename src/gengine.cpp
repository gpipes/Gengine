#include <iostream>
#include "gengine.hpp"
#include "sprite.hpp"

namespace {
    static const double msPerFrame60FPS = 16.667;
}

Gengine::Gengine(std::string name, int width, int height, bool fullscreen)
    : _screenMan(std::make_shared<ScreenManager>(name, width, height, fullscreen)),
      _inputMan(std::make_shared<InputManager>()),
      _componentMan(std::make_shared<ComponentManager>()),
      _systemMan(std::make_shared<SystemManager>(_componentMan, _inputMan, _screenMan)),
      _nextEntityID(0)
{
    SDL_Init(0);
    _screenMan->init();
    _systemMan->registerEndTickSystem(systemDraw,
                                      {std::type_index(typeid(Sprite)),
                                       std::type_index(typeid(Position))});
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
        while (SDL_PollEvent(&e)) {
            _inputMan->addInputEvent(e);
        }

        if (_inputMan->isQuit()) {
            isRunning = false;
            continue;
        }

        _systemMan->tick();
        _inputMan->clearInputEvents();

        endFrameTime = SDL_GetTicks();
        frameDelta = endFrameTime - startFrameTime;
        if (frameDelta < msPerFrame60FPS) {
            SDL_Delay(static_cast<Uint32>(msPerFrame60FPS - frameDelta));
        }
    }
}

void Gengine::loadSpriteComponents() {
    _screenMan->loadSpriteComponents(_componentMan);
}

EntityID Gengine::createEntity() {
    EntityID previousID = _nextEntityID;
    _nextEntityID++;
    return previousID;
}

void Gengine::registerSystem(SystemPtr system, ComponentSignature signature) {
    _systemMan->registerSystem(system, signature);
}
