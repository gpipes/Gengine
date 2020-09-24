#include <fstream>
#include <boost/property_tree/json_parser.hpp>
#include "spriteinfo.hpp"

namespace pt = boost::property_tree;

SpriteInfo::SpriteInfo()
    : _configFile(),
      _spriteStateMap()
{}

SpriteInfo::SpriteInfo(const std::string &configPath)
    : _configFile()
{
    pt::json_parser::read_json(configPath, _configFile);
}

void SpriteInfo::parseConfig(const std::string &configPath) {
    pt::json_parser::read_json(configPath, _configFile);
}

Rectangle SpriteInfo::getSpriteRectangle() const {
    return Rectangle(
        _configFile.get<int>("SpriteRect.width"),
        _configFile.get<int>("SpriteRect.height")
        );
}

int SpriteInfo::getOutputFactor() const {
    return _configFile.get("OutputFactor", 1);
}

std::unordered_map<std::string, AnimationVector> SpriteInfo::getSpriteStateMap() {
    if (!_spriteStateMap.empty()) {
        return _spriteStateMap;
    }
    std::unordered_map<std::string, AnimationVector> spriteStates;
    pt::ptree spriteStateMapList = _configFile.get_child("SpriteStateMapList");
    for(auto spriteStateMapPair : spriteStateMapList) {
        pt::ptree spriteStateMap = spriteStateMapPair.second;
        bool isAnim = spriteStateMap.get<bool>("isAnim");
        bool isLoop = spriteStateMap.get<bool>("isLoop");
        std::string stateName = spriteStateMap.get<std::string>("stateName");
        std::vector<AnimationInfo> animInfoVector;
        for(auto animInfoPair : spriteStateMap.get_child("animInfo")) {
            pt::ptree animInfo = animInfoPair.second;
            animInfoVector.push_back(
                {
                    {
                        animInfo.get<int>("Position.x"),
                        animInfo.get<int>("Position.y")
                    },
                    animInfo.get<int>("Duration")
                }
                );
        }
        spriteStates[stateName] = AnimationVector(animInfoVector, isAnim, isLoop);
    }
    _spriteStateMap = spriteStates;
    return spriteStates;
}

std::string SpriteInfo::getDefaultState() const {
    return _configFile.get<std::string>("DefaultState");
}
