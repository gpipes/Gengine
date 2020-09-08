#include "gameobjectbase.hpp"

GameObjectBase::GameObjectBase(std::string imgPath, std::string configPath)
    : _sprite(imgPath, configPath),
      _position()
{}

void GameObjectBase::update(const InputManager&, GameEventList&) {}

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

bool GameObjectBase::hasRecursiveGameObjects() const {
    return !_gameObjectComponents.empty();
}

GameObjectList GameObjectBase::getRecursiveGameObjects() const {
    return _gameObjectComponents;
}
