#pragma once
#include <vector>
#include <memory>
#include <SDL.h>

class Gengine;
class ScreenManager;
class UpdateManager;
class GameObjectBase;

typedef std::vector<std::shared_ptr<GameObjectBase>> GameWorld;
typedef std::shared_ptr<GameObjectBase> GameObjectPtr;
typedef std::shared_ptr<SDL_Texture> TexturePtr;
