#pragma once

#include <vector>
#include <string>
#include "fwd.hpp"
#include "screenmanager.hpp"
#include "inputmanager.hpp"
#include "componentmanager.hpp"
#include "systemmanager.hpp"

class Gengine {
public:
    Gengine(std::string name, int width, int height, bool fullscreen);
    ~Gengine();

    EntityID createEntity();
    template<typename T, typename ... Types> void giveEntityComponent(EntityID, Types ...);

    void run();
    void loadSpriteComponents();

    void registerSystem(SystemPtr, ComponentSignature);

private:
    ScreenManager _screenMan;
    InputManager _inputMan;
    ComponentManager _componentMan;
    SystemManager _systemMan;
    EntityID _nextEntityID;
};

template<typename T, typename ... Types>
void Gengine::giveEntityComponent(EntityID id, Types ... args) {
    _systemMan.invalidateSystemCache();
    _componentMan.addComponentForEntity<T>(id, args...);
}
