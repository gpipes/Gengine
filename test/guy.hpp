#pragma once
#include "gengine.hpp"
#include "sprite.hpp"

struct GuyRunning {};

class Guy {
public:
    Guy(Gengine& gengine, Position loc);
};

void guyRunningSystem(std::set<EntityID>& entities,
                      std::shared_ptr<ComponentManager> componentMan,
                      std::shared_ptr<InputManager> inputMan,
                      Gengine*);
