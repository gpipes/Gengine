#include "sprite.hpp"

Sprite::Sprite(std::string path, long width, long height, int factor)
	: _path(path),
	_spriteRect(width, height),
	_outputFactor(factor),
	_stateSpriteMap(),
	_currentAnimationState(0),
	_currentAnimationFrames(0),
	_currentAnimationIndex(0)
{}

void Sprite::setTexture(std::shared_ptr<SDL_Texture> texture) {
	_texture = texture;
}

void Sprite::addAnimationState(int state, AnimationVector animationInfo) {
	_stateSpriteMap[state] = animationInfo;
}

void Sprite::setCurrentAnimationState(int state) {
	if (_stateSpriteMap.find(state) != _stateSpriteMap.end()) {
		_currentAnimationState = state;
		_currentAnimationFrames = 0;
		_currentAnimationIndex = 0;
	}
}

AnimationInfo Sprite::getCurrentAnimationInfo() const {
	if (_stateSpriteMap.find(_currentAnimationState) == _stateSpriteMap.end()
		|| _stateSpriteMap.at(_currentAnimationState).frameInfo.size() <= _currentAnimationIndex ) {	
		return { {0, 0}, 0 };
	}

	return _stateSpriteMap.at(_currentAnimationState).frameInfo[_currentAnimationIndex];
}

void Sprite::incrementAnimation() {
	if (_stateSpriteMap.find(_currentAnimationState) == _stateSpriteMap.end())
		return;
	
	AnimationVector currentAnimVect = _stateSpriteMap.at(_currentAnimationState);
	if (!currentAnimVect.isAnimated)
		return;

	if (!currentAnimVect.isLooped && _currentAnimationIndex == currentAnimVect.frameInfo.size() - 1)
		return;

	// at this point it's animated and is either looped or has frames left to display
	
	if (currentAnimVect.frameInfo[_currentAnimationIndex].totalFrames > _currentAnimationFrames) {
		_currentAnimationFrames++;
		return;
	}

	_currentAnimationFrames = 0;

	if (currentAnimVect.frameInfo.size() - 1 == _currentAnimationIndex) {
		_currentAnimationIndex = 0;
		return;
	}

	_currentAnimationIndex++;
}

DisplayRectangle Sprite::getDisplayRect() const {
	AnimationInfo currentAnimationInfo = getCurrentAnimationInfo();

	return {
		{
			currentAnimationInfo.pos.x * _spriteRect.width,
			currentAnimationInfo.pos.y * _spriteRect.height
		},
		_spriteRect.width,
		_spriteRect.height
	};
}

Rectangle Sprite::getOutputRect() const {
	return {
		_spriteRect.width * _outputFactor,
		_spriteRect.height * _outputFactor
	};
}

std::shared_ptr<SDL_Texture> Sprite::texture() const {
	return _texture;
}

long Sprite::width() const {
	return _spriteRect.width;
}

long Sprite::height() const {
	return _spriteRect.height;
}

std::string Sprite::path() const {
	return _path;
}
