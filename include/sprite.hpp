#pragma once
#include <string>
#include <memory>
#include <vector>
#include <map>
#include "Fwd.hpp"
#include "utility.hpp"

class Sprite {
public:
    Sprite(std::string imgPath, std::string configPath);
	
    std::string imgPath() const;
    long width() const;
    long height() const;
	
    TexturePtr texture() const;
    void setTexture(TexturePtr texture);

    // Display rectangle on sprite sheet to draw
    DisplayRectangle getDisplayRect() const;
    // Scaled output rectangle
    Rectangle getOutputRect() const;

    void setCurrentAnimationState(const std::string &state);
    void incrementAnimation();
private:
    TexturePtr _texture;
    Rectangle _spriteRect;
    std::string _imgPath;
    int _outputFactor;

    AnimationInfo getCurrentAnimationInfo() const;
    std::map<std::string, AnimationVector> _spriteStateMap;
    std::string _currentAnimationState;
    int _currentAnimationFrames;
    int _currentAnimationIndex;
};
