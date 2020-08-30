#include "gameobjectbase.hpp"

GameObject::GameObject() {}

GameObjectBase::GameObject(std::string path) {
	_spriteSheetPath = path;
}

void GameObjectBase::setSpriteSheetTexture(std::shared_ptr<SDL_Texture> texture);