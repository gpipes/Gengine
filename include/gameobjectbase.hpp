#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>
#include "Fwd.hpp"
#include "utility.hpp"
#include "sprite.hpp"

class GameObjectBase {
public:
    GameObjectBase(std::string imgPath, std::string configPath);


public:
    // Sprite functions to set sprite
    void setCurrentAnimationState(const std::string &state);

private:
    // Sprite functions for screen manager
    std::string getSpriteSheetPath() const;
    DisplayRectangle getSpriteDisplayRect() const;
    DisplayRectangle getOutputRect() const;
    TexturePtr getSpriteSheetTexture() const;
    void setSpriteSheetTexture(TexturePtr texture);
    void incrementAnimation();

private:
    Point _position;
    Sprite _sprite;

    // functions from the engine that need to load state
    friend class ScreenManager;
};
