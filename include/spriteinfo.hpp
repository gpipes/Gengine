#pragma once
#include <string>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include "utility.hpp"

class SpriteInfo {
public:
    SpriteInfo();
    SpriteInfo(const std::string &configPath);
    void parseConfig(const std::string &configPath);
    Rectangle getSpriteRectangle() const;
    int getOutputFactor() const;
    std::unordered_map<std::string, AnimationVector> getSpriteStateMap() const;
    std::string getDefaultState() const;
private:
    boost::property_tree::ptree _configFile;
};
