#pragma once
#include "gengine.hpp"
#include "sprite.hpp"

struct GuyRunning {};
struct Destination {
    Destination() = default;
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

void guyRunningSystem(const std::vector<EntityID>&,
                      ComponentManager&,
                      InputManager&,
                      ScreenManager&);
