#include <fstream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
#pragma clang diagnostic ignored "-W#pragma-messages"
#include <boost/property_tree/json_parser.hpp>
#pragma clang diagnostic pop

#include "spriteinfo.hpp"

namespace pt = boost::property_tree;

SpriteInfo::SpriteInfo()
    : _configFile(),
      _spriteStateMap(),
      _spriteRectangle(),
      _rectangleInitialized(false),
      _outputFactor(1),
      _outputFactorInitialized(false),
      _defaultState(),
      _defaultStateInitialized(false) {}

SpriteInfo::SpriteInfo(const std::string &configPath) : _configFile() {
  pt::json_parser::read_json(configPath, _configFile);
}

void SpriteInfo::parseConfig(const std::string &configPath) {
  pt::json_parser::read_json(configPath, _configFile);
}

Rectangle SpriteInfo::getSpriteRectangle() {
  if (!_rectangleInitialized) {
    _spriteRectangle = Rectangle(_configFile.get<int>("SpriteRect.width"),
                                 _configFile.get<int>("SpriteRect.height"));
    _rectangleInitialized = true;
  }
  return _spriteRectangle;
}

int SpriteInfo::getOutputFactor() {
  if (!_outputFactorInitialized) {
    _outputFactor = _configFile.get("OutputFactor", 1);
    _outputFactorInitialized = true;
  }

  return _outputFactor;
}

std::unordered_map<int, AnimationVector> SpriteInfo::getSpriteStateMap() {
  if (!_spriteStateMap.empty()) {
    return _spriteStateMap;
  }
  std::unordered_map<int, AnimationVector> spriteStates;
  pt::ptree spriteStateMapList = _configFile.get_child("SpriteStateMapList");
  int i = 0;
  for (auto spriteStateMapPair : spriteStateMapList) {
    pt::ptree spriteStateMap = spriteStateMapPair.second;
    bool isAnim = spriteStateMap.get<bool>("isAnim");
    bool isLoop = spriteStateMap.get<bool>("isLoop");
    std::vector<AnimationInfo> animInfoVector;
    for (auto animInfoPair : spriteStateMap.get_child("animInfo")) {
      pt::ptree animInfo = animInfoPair.second;
      animInfoVector.push_back(
          {{animInfo.get<int>("Position.x"), animInfo.get<int>("Position.y")},
           animInfo.get<uint32_t>("Duration")});
    }
    spriteStates[i] = AnimationVector(animInfoVector, isAnim, isLoop);
    ++i;
  }
  _spriteStateMap = spriteStates;
  return spriteStates;
}

int SpriteInfo::getDefaultState() {
  if (!_defaultStateInitialized) {
    _defaultState = _configFile.get("DefaultState", 0);
    _defaultStateInitialized = true;
  }
  return _defaultState;
}
