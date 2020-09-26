#pragma once

#include <memory>
#include <vector>
#include <string>
#include "SDL.h"
#include "fwd.hpp"
#include "utility.hpp"

class ScreenManager {
public:
    ScreenManager(std::string, int, int, bool);
    void init();
    void loadSpriteComponents(std::shared_ptr<ComponentManager>);
    RendererPtr renderer() const;

private:
    void draw(const GameObjectBase& gameObject);

    std::shared_ptr<SDL_Window> _window;
    std::shared_ptr<SDL_Renderer> _renderer;
    std::string _windowName;
    Rectangle _windowDimensions;
    bool _isFullscreen;

    std::unordered_map<std::string, TexturePtr> _bmpCache;
};

void systemDraw(std::set<EntityID>&,
                std::shared_ptr<ComponentManager>,
                std::shared_ptr<InputManager>,
                std::shared_ptr<ScreenManager>);
