#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>
#include "SDL.h"
#include "utility.hpp"
#include "sprite.hpp"

class ScreenManager;

class GameObjectBase {
public:
	GameObjectBase(std::string path, long width, long height, int factor);

	std::string getSpriteSheetPath() const;
	DisplayRectangle getSpriteDisplayRect() const;
	DisplayRectangle getOutputRect() const;

	std::shared_ptr<SDL_Texture> getSpriteSheetTexture() const;
	void setSpriteSheetTexture(std::shared_ptr<SDL_Texture> texture);

	void addAnimationState(int state, AnimationVector animInfo);
	void setCurrentAnimationState(int state);
	void incrementAnimation();

private:
	Point _position;
	Sprite _sprite;
};