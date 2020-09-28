#include "sprite.hpp"

std::unordered_map<std::string, SpriteInfo> Sprite::_loadedConfigs;

Sprite::Sprite(std::string imgPath, std::string configPath)
    : _imgPath(imgPath),
      _spriteRect(0,0),
      _outputFactor(0),
      _spriteStateMap(),
      _currentAnimationFrames(0),
      _currentAnimationIndex(0),
      _currentAnimState()
{
    if (_loadedConfigs.find(configPath) == _loadedConfigs.end()) {
		_loadedConfigs[configPath] = SpriteInfo();
		_loadedConfigs[configPath].parseConfig(configPath);
    }
	SpriteInfo* info = &_loadedConfigs[configPath];

    _spriteRect = info->getSpriteRectangle();
    _outputFactor = info->getOutputFactor();
    _spriteStateMap = info->getSpriteStateMap();
    _currentAnimState = info->getDefaultState();
    _currentAnimVect = _spriteStateMap[_currentAnimState];

    _currentDisplayRect.x
        = _currentAnimVect.frameInfo[_currentAnimationIndex].pos.x * _spriteRect.width;
    _currentDisplayRect.y
        = _currentAnimVect.frameInfo[_currentAnimationIndex].pos.y * _spriteRect.height;

    _currentDisplayRect.w = _spriteRect.width;
    _currentDisplayRect.h = _spriteRect.height;
    _outputRect.width = _spriteRect.width * _outputFactor;
    _outputRect.height = _spriteRect.height * _outputFactor;
}

void Sprite::setTexture(TexturePtr texture) {
    _texture = texture;
}

void Sprite::setCurrentAnimationState(const std::string &state) {
    if (state != _currentAnimState) {
        _currentAnimationFrames = 0;
        _currentAnimationIndex = 0;
        _currentAnimState = state;
        _currentAnimVect = _spriteStateMap[state];
    }
}

void Sprite::incrementAnimation() {
    if (!_currentAnimVect.isAnimated)
        return;

    if (!_currentAnimVect.isLooped && _currentAnimationIndex == _currentAnimVect.frameInfo.size() - 1)
        return;

    // at this point it's animated and is either looped or has frames left to display
	
    if (_currentAnimVect.frameInfo[_currentAnimationIndex].totalFrames > _currentAnimationFrames) {
        ++_currentAnimationFrames;
        return;
    }

    _currentAnimationFrames = 0;

    if (_currentAnimVect.frameInfo.size() - 1 == _currentAnimationIndex) {
        _currentAnimationIndex = 0;
    }
    else {
        ++_currentAnimationIndex;
    }
    _currentDisplayRect.x
        = _currentAnimVect.frameInfo[_currentAnimationIndex].pos.x * _spriteRect.width;
    _currentDisplayRect.y
        = _currentAnimVect.frameInfo[_currentAnimationIndex].pos.y * _spriteRect.height;
}

const DisplayRectangle& Sprite::getDisplayRect() const {
    return _currentDisplayRect;
}

const Rectangle& Sprite::getOutputRect() const {
    return _outputRect;
}

const TexturePtr& Sprite::texture() const {
    return _texture;
}

long Sprite::width() const {
    return _spriteRect.width;
}

long Sprite::height() const {
    return _spriteRect.height;
}

std::string Sprite::imgPath() const {
    return _imgPath;
}
