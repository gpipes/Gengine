#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>
#include "SDL.h"
#include "utility.hpp"

class Sprite {
public:
	Sprite(std::string path, long width, long height, int factor);
	
	std::string path() const;
	long width() const;
	long height() const;
	
	std::shared_ptr<SDL_Texture> texture() const;
	void setTexture(std::shared_ptr<SDL_Texture> texture);

	// Display rectangle on sprite sheet to draw
	DisplayRectangle getDisplayRect() const;
	// Scaled output rectangle
	Rectangle getOutputRect() const;

	void addAnimationState(int state, AnimationVector animationInfo);
	void setCurrentAnimationState(int state);
	void incrementAnimation();
private:
	std::shared_ptr<SDL_Texture> _texture;
	Rectangle _spriteRect;
	std::string _path;
	int _outputFactor;

	AnimationInfo getCurrentAnimationInfo() const;
	std::map<int, AnimationVector> _stateSpriteMap;
	int _currentAnimationState;
	int _currentAnimationFrames;
	int _currentAnimationIndex;
};