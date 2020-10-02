#include <iostream>
#include "screenmanager.hpp"
#include "sprite.hpp"
#include "componentmanager.hpp"
#include "gengine.hpp"
#include "SDL.h"

ScreenManager::ScreenManager(std::string name, int width, int height, bool fullscreen)
    : _windowName(name),
      _windowDimensions(width, height),
      _isFullscreen(fullscreen)
{}

void ScreenManager::init() {
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);

    std::uint32_t windowFlags = 0;
    if (_isFullscreen) {
        windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN;
    }
    _window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow(
            _windowName.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            _windowDimensions.width, _windowDimensions.height, windowFlags),
        SDL_DestroyWindow);

    _renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED),
                                              SDL_DestroyRenderer);

}

void ScreenManager::loadSpriteComponents(ComponentManager& componentMan) {
    std::vector<EntityID> spriteEntities = componentMan.getEntitiesWithSignature({
            std::type_index(typeid(Sprite))
                });
    std::vector<Sprite>& spriteComponents = componentMan.get<Sprite>();

    for (auto& entity : spriteEntities) {
        Sprite& entitySprite = spriteComponents[entity];
        if (_bmpCache.find(entitySprite.imgPath()) != _bmpCache.end()) {
            entitySprite.setTexture(_bmpCache[entitySprite.imgPath()]);
            continue;
        }

        std::shared_ptr<SDL_Surface> surface(SDL_LoadBMP(entitySprite.imgPath().c_str()), SDL_FreeSurface);
        SDL_SetColorKey(surface.get(), SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

        TexturePtr texture = TexturePtr(
            SDL_CreateTextureFromSurface(_renderer.get(), surface.get()),
            SDL_DestroyTexture);
        _bmpCache[entitySprite.imgPath()] = texture;
        entitySprite.setTexture(texture);
    }
}

const RendererPtr& ScreenManager::renderer() const {
    return _renderer;
}

void incrementAnimation(const std::vector<EntityID>& entities,
                        ComponentManager& componentMan,
                        InputManager&,
                        ScreenManager&) {
    std::vector<Sprite>& spriteComponents = componentMan.get<Sprite>();

    for (auto& entity : entities) {
        spriteComponents[entity].incrementAnimation();
    }
}


void systemDraw(const std::vector<EntityID>& entities,
                ComponentManager& componentMan,
                InputManager&,
                ScreenManager& screenMan) {
    std::vector<Sprite>& spriteComponents = componentMan.get<Sprite>();
    std::vector<Position>& positionComponents = componentMan.get<Position>();

    SDL_RenderClear(screenMan.renderer().get());
    for (auto& entity : entities) {
        const Sprite& entitySprite = spriteComponents[entity];
        const Position& entityPosition = positionComponents[entity];

        const SDL_Rect& displayRect = entitySprite.getDisplayRect();
        const Rectangle& scaledOutputSize = entitySprite.getOutputRect();
        const SDL_Rect outputRect = {
                entityPosition.x, entityPosition.y,
                scaledOutputSize.width, scaledOutputSize.height
            };

        SDL_RenderCopy(screenMan.renderer().get(), entitySprite.texture().get(), &displayRect, &outputRect);
    }
    SDL_RenderPresent(screenMan.renderer().get());
}
