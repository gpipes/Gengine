#pragma once
#include <vector>
#include <memory>
#include <cstdint>
#include <map>
#include <set>
#include <typeindex>
#include <functional>
#include <SDL.h>

struct Component {};

class Gengine;
class ScreenManager;
class UpdateManager;
class GameObjectBase;
class GameEvent;
class ComponentManager;

typedef std::size_t EntityID;
typedef std::set<std::type_index> ComponentSignature;
typedef std::function<void(std::set<EntityID>,
                           std::shared_ptr<ComponentManager>)> System;
typedef std::vector<std::pair<System, ComponentSignature>> SystemList;
typedef std::shared_ptr<GameObjectBase> GameObjectPtr;
typedef std::vector<GameObjectPtr> GameObjectList;
typedef std::shared_ptr<SDL_Texture> TexturePtr;
typedef std::shared_ptr<GameEvent> GameEventPtr;
typedef std::vector<GameEventPtr> GameEventList;
