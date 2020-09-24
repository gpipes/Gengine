#include <iostream>
#include "screenmanager.hpp"
#include "sprite.hpp"
#include "componentmanager.hpp"
#include "SDL.h"

ScreenManager::ScreenManager(std::string name, int width, int height)
    : _windowName(name),
      _windowDimensions(width, height)
{}

void ScreenManager::init() {
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(0, &dm);

    _window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow(
            _windowName.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            _windowDimensions.width, _windowDimensions.height, 0), SDL_DestroyWindow);

    _renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED),
                                              SDL_DestroyRenderer);

}

void ScreenManager::loadSpriteComponents(std::shared_ptr<ComponentManager> componentMan) {
    std::set<EntityID> spriteEntities = componentMan->getEntitiesWithSignature({
            std::type_index(typeid(Sprite))
                });
    for (auto& entity : spriteEntities) {
        Sprite& entitySprite = componentMan->getComponentForEntity<Sprite>(entity);
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

std::shared_ptr<System> ScreenManager::getSystem() {
    return
        std::make_shared<System>(
            [this](std::set<EntityID>& entities, std::shared_ptr<ComponentManager> componentMan,
                   std::shared_ptr<InputManager>, Gengine*) {
                this->systemDraw(entities, componentMan);
        });
}

void ScreenManager::systemDraw(std::set<EntityID>& entities, std::shared_ptr<ComponentManager> componentMan) {
    SDL_RenderClear(_renderer.get());
    for (auto& entity : entities) {
        Sprite& entitySprite = componentMan->getComponentForEntity<Sprite>(entity);
        if (!entitySprite.isLoaded()) {
            continue;
        }

        Point& entityPosition = componentMan->getComponentForEntity<Position>(entity);

        entitySprite.incrementAnimation();

        SDL_Rect displayRect = sdlRectFromRectangle(entitySprite.getDisplayRect());
        Rectangle scaledOutputSize = entitySprite.getOutputRect();
        SDL_Rect outputRect = sdlRectFromRectangle({
                {entityPosition.x, entityPosition.y},
                scaledOutputSize.width, scaledOutputSize.height
            });

        SDL_RenderCopy(_renderer.get(), entitySprite.texture().get(), &displayRect, &outputRect);
    }
    SDL_RenderPresent(_renderer.get());
}
