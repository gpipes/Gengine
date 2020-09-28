#pragma once
#include <vector>
#include <memory>
#include <cstdint>
#include <map>
#include <set>
#include <typeindex>
#include <functional>
#include <SDL.h>

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
typedef void (*SystemPtr)(const std::vector<EntityID>&,
                          std::shared_ptr<ComponentManager>,
                          std::shared_ptr<InputManager>,
                          std::shared_ptr<ScreenManager>);
typedef std::set<std::pair<SystemPtr,
                           ComponentSignature>> SystemList;
typedef std::shared_ptr<GameObjectBase> GameObjectPtr;
typedef std::vector<GameObjectPtr> GameObjectList;
typedef std::shared_ptr<SDL_Texture> TexturePtr;
typedef std::shared_ptr<GameEvent> GameEventPtr;
typedef std::vector<GameEventPtr> GameEventList;
typedef SDL_Rect DisplayRectangle;
