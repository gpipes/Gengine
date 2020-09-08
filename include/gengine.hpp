#pragma once

#include <vector>
#include <string>
#include "Fwd.hpp"
#include "screenmanager.hpp"
#include "inputmanager.hpp"
#include "updatemanager.hpp"

class Gengine {
public:
    Gengine(std::string name, int width, int height);
    ~Gengine();

    void run();

    // effecting gameworld state
    void setAndLoadGameWorld(GameObjectList world);
    void setGameWorld(GameObjectList world);
    void loadGameWorld();

private:
    ScreenManager _screenMan;
    InputManager _inputMan;
    UpdateManager _updateMan;
    GameObjectList _gameWorld;
};
