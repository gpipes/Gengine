#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>
#include "Fwd.hpp"
#include "utility.hpp"
#include "sprite.hpp"
#include "inputmanager.hpp"

class GameObjectBase {
public:
    GameObjectBase(std::string, std::string);
    virtual void update(const InputManager&, GameEventList&);

public:
    // Sprite functions to set sprite
    void setCurrentAnimationState(const std::string&);

private:
    // Sprite functions for screen manager
    std::string getSpriteSheetPath() const;
    DisplayRectangle getSpriteDisplayRect() const;
    DisplayRectangle getOutputRect() const;
    TexturePtr getSpriteSheetTexture() const;
    void setSpriteSheetTexture(TexturePtr);
    void incrementAnimation();
    bool hasRecursiveGameObjects() const;
    GameObjectList getRecursiveGameObjects() const;

protected:
    // an object can be an object itself or manage other game objects
    // this is protected because game objects can write their own logic
    // to manage this but nobody else should get at others
    GameObjectList _gameObjectComponents;

private:
    Point _position;
    Sprite _sprite;

    // functions from the engine that need to load state
    friend class ScreenManager;
};
