#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>
#include "fwd.hpp"
#include "utility.hpp"
#include "spriteinfo.hpp"


class Sprite {
public:
    Sprite() = default;
    Sprite(Sprite&&) = default;
    Sprite& operator=(Sprite&&) = default;
    Sprite(std::string imgPath, std::string configPath);

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;
	
    const std::string& imgPath() const;
    long width() const;
    long height() const;
    const TexturePtr& texture() const;
    const DisplayRectangle& getDisplayRect() const;
    const Rectangle& getOutputRect() const;

    void setTexture(TexturePtr);
    void setCurrentAnimationState(const uint32_t &state);
    void incrementAnimation();

private:
    TexturePtr _texture;
    Rectangle _spriteRect;
    std::string _imgPath;
    int _outputFactor;

    std::unordered_map<int, AnimationVector> _spriteStateMap;
    AnimationVector _currentAnimVect;
    DisplayRectangle _currentDisplayRect;
    Rectangle _outputRect;
    uint32_t _currentAnimationFrames;
    uint32_t _currentAnimationIndex;
    uint32_t _currentAnimState;

    static std::unordered_map<std::string, SpriteInfo> _loadedConfigs;
};
