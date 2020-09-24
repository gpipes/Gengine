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
    template<typename T> void giveEntityComponent(EntityID,std::shared_ptr<T>);

    void run();
    void loadSpriteComponents();

    void registerSystem(std::shared_ptr<System>, ComponentSignature);

private:
    ScreenManager _screenMan;

    std::shared_ptr<InputManager> _inputMan;
    std::shared_ptr<ComponentManager> _componentMan;
    std::shared_ptr<SystemManager> _systemMan;
    EntityID _nextEntityID;
};

template<typename T>
void Gengine::giveEntityComponent(EntityID id, std::shared_ptr<T> component) {
    _systemMan->invalidateSystemCache();
    _componentMan->addComponentForEntity(id, component);
}
