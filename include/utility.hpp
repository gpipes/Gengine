#pragma once
#include <vector>
#include "SDL.h"

struct Point {
    Point()
        : x(0),
          y(0)
        {}

    Point(int x_, int y_)
        : x(x_),
          y(y_)
        {}

    Point(const Point& p)
        : x(p.x),
          y(p.y)
        {}

    long x, y;
};

typedef Point Position;

struct Rectangle {
    Rectangle(long w, long h)
        : width(w),
          height(h)
        {}

    Rectangle()
        : width(0),
          height(0)
        {}

    long width, height;
};

struct DisplayRectangle {
    Point loc;
    long width = 0, height = 0;
};

struct AnimationInfo {
    Point pos;
    int totalFrames;
};

struct AnimationVector {
    AnimationVector() {
        frameInfo.push_back({ {0,0}, 0 });
        isAnimated = false;
        isLooped = false;
    }

    AnimationVector(std::vector<AnimationInfo> animInfo, bool isAnim, bool isLoop)
        : frameInfo(animInfo),
          isAnimated(isAnim),
          isLooped(isLoop)
        {}

    std::vector<AnimationInfo> frameInfo;
    bool isAnimated;
    bool isLooped;
};

SDL_Rect sdlRectFromRectangle(DisplayRectangle rect);
