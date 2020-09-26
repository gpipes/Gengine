#pragma once
#include "gengine.hpp"
#include "sprite.hpp"

struct GuyRunning {};
struct Destination {
    Destination(long x, long y, int v)
        : dest(x,y),
          velocity(v)
        {}
    Position dest;
    int velocity;
};

class Guy {
public:
    Guy(Gengine& gengine, Position loc);
};

void guyRunningSystem(std::set<EntityID>& entities,
                      std::shared_ptr<ComponentManager> componentMan,
                      std::shared_ptr<InputManager> inputMan,
                      Gengine*);
