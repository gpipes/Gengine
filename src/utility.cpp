#include "utility.hpp"

SDL_Rect sdlRectFromRectangle(DisplayRectangle rect) {
    return {
        rect.loc.x,
        rect.loc.y,
        rect.width,
        rect.height
    };
}
