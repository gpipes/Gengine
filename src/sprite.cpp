#include "sprite.hpp"
#include "spriteinfo.hpp"

Sprite::Sprite(std::string imgPath, std::string configPath)
    : _imgPath(imgPath),
      _spriteRect(0,0),
      _outputFactor(0),
      _spriteStateMap(),
      _currentAnimationState(),
      _currentAnimationFrames(0),
      _currentAnimationIndex(0)
{
    SpriteInfo info(configPath);
    _spriteRect = info.getSpriteRectangle();
    _outputFactor = info.getOutputFactor();
    _spriteStateMap = info.getSpriteStateMap();
}

void Sprite::setTexture(TexturePtr texture) {
    _texture = texture;
}

void Sprite::setCurrentAnimationState(const std::string &state) {
    if (_spriteStateMap.find(state) != _spriteStateMap.end()) {
        _currentAnimationState = state;
        _currentAnimationFrames = 0;
        _currentAnimationIndex = 0;
    }
}

AnimationInfo Sprite::getCurrentAnimationInfo() const {
    if (_spriteStateMap.find(_currentAnimationState) == _spriteStateMap.end()
        || _spriteStateMap.at(_currentAnimationState).frameInfo.size() <= _currentAnimationIndex ) {
        return { {0, 0}, 0 };
    }

    return _spriteStateMap.at(_currentAnimationState).frameInfo[_currentAnimationIndex];
}

void Sprite::incrementAnimation() {
    if (_spriteStateMap.find(_currentAnimationState) == _spriteStateMap.end())
        return;
	
    AnimationVector currentAnimVect = _spriteStateMap.at(_currentAnimationState);
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
