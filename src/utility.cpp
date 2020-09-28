#include "utility.hpp"

SDL_Rect sdlRectFromRectangle(SDL_Rect rect) {
    return {
        rect.x,
        rect.y,
        rect.w,
        rect.h
    };
}
