#include "screenmanager.hpp"
#include "gameobjectbase.hpp"
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

void ScreenManager::load(GameObjectBase& gameObject) {
    std::shared_ptr<SDL_Surface> surface(SDL_LoadBMP(gameObject.getSpriteSheetPath().c_str()), SDL_FreeSurface);
    SDL_SetColorKey(surface.get(), SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    TexturePtr texture = TexturePtr(
        SDL_CreateTextureFromSurface(_renderer.get(), surface.get()),
        SDL_DestroyTexture);
    gameObject.setSpriteSheetTexture(texture);
}

void ScreenManager::drawWorld(GameWorld world) {
    SDL_RenderClear(_renderer.get());
    for (auto gameObject : world) {
        draw(*gameObject);
        gameObject->incrementAnimation();
    }
    SDL_RenderPresent(_renderer.get());
}

void ScreenManager::draw(const GameObjectBase& gameObject) {

    // this is where the camera should go.
    // TODO use a default camerat that always keeps 0,0 in the top left
    // TODO inherit from default camera and have it follow a gameObject
    SDL_Rect displayRect = sdlRectFromRectangle(gameObject.getSpriteDisplayRect());
    SDL_Rect outputRect = sdlRectFromRectangle(gameObject.getOutputRect());
    SDL_RenderCopy(_renderer.get(), gameObject.getSpriteSheetTexture().get(), &displayRect, &outputRect);
}
