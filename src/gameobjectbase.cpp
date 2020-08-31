#include "gameobjectbase.hpp"

GameObjectBase::GameObjectBase(std::string path, long width, long height, int factor)
    : _sprite(path, width, height, factor),
      _position()
{}

std::string GameObjectBase::getSpriteSheetPath() const {
    return _sprite.path();
}

void GameObjectBase::incrementAnimation() {
    _sprite.incrementAnimation();
}

DisplayRectangle GameObjectBase::getSpriteDisplayRect() const {
    return _sprite.getDisplayRect();
}

DisplayRectangle GameObjectBase::getOutputRect() const {
    Rectangle scaledOutputSize = _sprite.getOutputRect();
    return {
        {_position.x, _position.y},
        scaledOutputSize.width, scaledOutputSize.height
    };
}

std::shared_ptr<SDL_Texture> GameObjectBase::getSpriteSheetTexture() const {
    return _sprite.texture();
}

void GameObjectBase::setSpriteSheetTexture(std::shared_ptr<SDL_Texture> texture) {
    _sprite.setTexture(texture);
}

void GameObjectBase::addAnimationState(int state, AnimationVector animInfo) {
    _sprite.addAnimationState(state, animInfo);
}

void GameObjectBase::setCurrentAnimationState(int state) {
    _sprite.setCurrentAnimationState(state);
}
