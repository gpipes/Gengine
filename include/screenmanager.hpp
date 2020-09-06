#pragma once

#include <memory>
#include <vector>
#include <string>
#include "SDL.h"
#include "Fwd.hpp"
#include "utility.hpp"

class ScreenManager {
public:
    ScreenManager(std::string name, int width, int height);
    void init();
    void load(GameObjectBase& gameObject);
    void drawWorld(GameWorld world);

private:
    void draw(const GameObjectBase& gameObject);

    std::shared_ptr<SDL_Window> _window;
    std::shared_ptr<SDL_Renderer> _renderer;
    std::string _windowName;
    Rectangle _windowDimensions;
};
