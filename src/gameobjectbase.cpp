#include "gameobjectbase.hpp"

GameObjectBase::GameObjectBase(std::string imgPath, std::string configPath)
    : _sprite(imgPath, configPath),
      _position()
{}

std::string GameObjectBase::getSpriteSheetPath() const {
    return _sprite.imgPath();
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

TexturePtr GameObjectBase::getSpriteSheetTexture() const {
    return _sprite.texture();
}

void GameObjectBase::setSpriteSheetTexture(TexturePtr texture) {
    _sprite.setTexture(texture);
}

void GameObjectBase::setCurrentAnimationState(const std::string &state) {
    _sprite.setCurrentAnimationState(state);
}
