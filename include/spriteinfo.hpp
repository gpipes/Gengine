#pragma once
#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include "utility.hpp"

class SpriteInfo {
public:
    SpriteInfo(const std::string &configPath);
    Rectangle SpriteInfo::getSpriteRectangle() const;
    int SpriteInfo::getOutputFactor() const;
    std::map<std::string, AnimationVector> SpriteInfo::getSpriteStateMap() const;
private:
    boost::property_tree::ptree _configFile;
};
