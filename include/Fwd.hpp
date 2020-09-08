#pragma once
#include <vector>
#include <memory>
#include <SDL.h>

class Gengine;
class ScreenManager;
class UpdateManager;
class GameObjectBase;
class GameEvent;

typedef std::shared_ptr<GameObjectBase> GameObjectPtr;
typedef std::vector<GameObjectPtr> GameObjectList;
typedef std::shared_ptr<SDL_Texture> TexturePtr;
typedef std::shared_ptr<GameEvent> GameEventPtr;
typedef std::vector<GameEventPtr> GameEventList;
