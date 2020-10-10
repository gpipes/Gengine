#pragma once
#include <string>
#include <unordered_map>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wlanguage-extension-token"
#include <boost/property_tree/ptree.hpp>
#pragma clang diagnostic pop

#include "utility.hpp"

class SpriteInfo {
 public:
  SpriteInfo();
  SpriteInfo(const std::string &configPath);
  void parseConfig(const std::string &configPath);
  Rectangle getSpriteRectangle();
  int getOutputFactor();
  std::unordered_map<int, AnimationVector> getSpriteStateMap();
  int getDefaultState();

 private:
  boost::property_tree::ptree _configFile;
  std::unordered_map<int, AnimationVector> _spriteStateMap;

  Rectangle _spriteRectangle;
  bool _rectangleInitialized;

  int _outputFactor;
  bool _outputFactorInitialized;

  int _defaultState;
  bool _defaultStateInitialized;
};
