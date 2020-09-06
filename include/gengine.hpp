#pragma once

#include <vector>
#include <string>
#include "Fwd.hpp"
#include "screenmanager.hpp"

class Gengine {
public:
    Gengine(std::string name, int width, int height);
    ~Gengine();

    void run();

    // effecting gameworld state
    void setAndLoadGameWorld(GameWorld world);
    void setGameWorld(GameWorld world);
    void loadGameWorld();

private:
    ScreenManager _screenMan;
    //UpdateManager _updateMan;
    GameWorld _gameWorld;
    const double _msPerFrame;
};
