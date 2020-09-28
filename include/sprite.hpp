#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>
#include "Fwd.hpp"
#include "utility.hpp"
#include "spriteinfo.hpp"


class Sprite {
public:
    Sprite() = default;
    Sprite(std::string imgPath, std::string configPath);
	
    std::string imgPath() const;
    long width() const;
    long height() const;

    const TexturePtr& texture() const;
    void setTexture(TexturePtr);


    // Display rectangle on sprite sheet to draw
    const DisplayRectangle& getDisplayRect() const;
    // Scaled output rectangle
    const Rectangle& getOutputRect() const;

    void setCurrentAnimationState(const std::string &state);
    void incrementAnimation();
private:
    TexturePtr _texture;
    Rectangle _spriteRect;
    std::string _imgPath;
    int _outputFactor;

    std::unordered_map<std::string, AnimationVector> _spriteStateMap;
    AnimationVector _currentAnimVect;
    DisplayRectangle _currentDisplayRect;
    Rectangle _outputRect;
    int _currentAnimationFrames;
    int _currentAnimationIndex;
    std::string _currentAnimState;

    static std::unordered_map<std::string, SpriteInfo> _loadedConfigs;
};
