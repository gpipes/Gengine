#pragma once

#include <vector>
#include <string>
#include "screenmanager.hpp"

class GameObjectBase;

class Gengine {
public:
    Gengine(std::string name, int width, int height);
    ~Gengine();

    void run();

    // effecting gameworld state
    void setAndLoadGameWorld(std::vector<std::shared_ptr<GameObjectBase>> world);
    void setGameWorld(std::vector<std::shared_ptr<GameObjectBase>> world);
    void loadGameWorld();

private:
    ScreenManager _screenMan;
    std::vector<std::shared_ptr<GameObjectBase>> _gameWorld;
    const double _msPerFrame;
};
