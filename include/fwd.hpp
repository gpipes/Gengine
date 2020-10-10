#pragma once
#include <SDL.h>

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <typeindex>
#include <vector>

class Gengine;
class ScreenManager;
class UpdateManager;
class GameObjectBase;
class GameEvent;
class ComponentManager;
class InputManager;
class Sprite;

typedef std::size_t EntityID;
typedef std::shared_ptr<SDL_Renderer> RendererPtr;
typedef std::set<std::type_index> ComponentSignature;

typedef void (*SystemPtr)(const std::vector<EntityID>&, ComponentManager&,
                          InputManager&, ScreenManager&);

typedef std::set<std::pair<SystemPtr, ComponentSignature>> SystemList;
typedef std::shared_ptr<GameObjectBase> GameObjectPtr;
typedef std::vector<GameObjectPtr> GameObjectList;
typedef std::shared_ptr<SDL_Texture> TexturePtr;
typedef std::shared_ptr<GameEvent> GameEventPtr;
typedef std::vector<GameEventPtr> GameEventList;
typedef SDL_Rect DisplayRectangle;
