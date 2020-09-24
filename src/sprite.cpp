#include "sprite.hpp"

std::unordered_map<std::string, SpriteInfo> Sprite::_loadedConfigs;

Sprite::Sprite(std::string imgPath, std::string configPath)
    : _imgPath(imgPath),
      _spriteRect(0,0),
      _outputFactor(0),
      _spriteStateMap(),
      _currentAnimationFrames(0),
      _currentAnimationIndex(0),
      _isLoaded(false),
      _currentAnimState()
{
    SpriteInfo info;
    if (_loadedConfigs.find(configPath) != _loadedConfigs.end()) {
        info = _loadedConfigs[configPath];
    }
    else {
        info.parseConfig(configPath);
        _loadedConfigs[configPath] = info;
    }

    _spriteRect = info.getSpriteRectangle();
    _outputFactor = info.getOutputFactor();
    _spriteStateMap = info.getSpriteStateMap();
    _currentAnimState = info.getDefaultState();
    _currentAnimVect = _spriteStateMap[_currentAnimState];

    _currentDisplayRect.loc.x
        = _currentAnimVect.frameInfo[_currentAnimationIndex].pos.x * _spriteRect.width;
    _currentDisplayRect.loc.y
        = _currentAnimVect.frameInfo[_currentAnimationIndex].pos.y * _spriteRect.height;

    _currentDisplayRect.width = _spriteRect.width;
    _currentDisplayRect.height = _spriteRect.height;
}

void Sprite::setTexture(TexturePtr texture) {
    _texture = texture;
    _isLoaded = true;
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
        _currentAnimationFrames++;
        return;
    }

    _currentAnimationFrames = 0;

    if (_currentAnimVect.frameInfo.size() - 1 == _currentAnimationIndex) {
        _currentAnimationIndex = 0;
    }
    else {
        _currentAnimationIndex++;
    }
    _currentDisplayRect.loc.x
        = _currentAnimVect.frameInfo[_currentAnimationIndex].pos.x * _spriteRect.width;
    _currentDisplayRect.loc.y
        = _currentAnimVect.frameInfo[_currentAnimationIndex].pos.y * _spriteRect.height;
}

DisplayRectangle Sprite::getDisplayRect() const {
    return _currentDisplayRect;
}

Rectangle Sprite::getOutputRect() const {
    return {
        _spriteRect.width * _outputFactor,
        _spriteRect.height * _outputFactor
    };
}

TexturePtr Sprite::texture() const {
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

bool Sprite::isLoaded() const {
    return _isLoaded;
}
