#include "systemmanager.hpp"
#include "componentmanager.hpp"

SystemManager::SystemManager(ComponentManager& componentMan,
                             InputManager& inputMan,
                             ScreenManager& screenMan)
    : _componentMan(componentMan),
      _inputMan(inputMan),
      _screenMan(screenMan)
{}

void SystemManager::registerSystem(SystemPtr system,
                                   ComponentSignature signature) {
    registerSystemToList(system, signature, _systems);
}

void SystemManager::registerBeginTickSystem(SystemPtr system,
                                            ComponentSignature signature) {
    registerSystemToList(system, signature, _beginTickSystems);
}

void SystemManager::registerEndTickSystem(SystemPtr system,
                                           ComponentSignature signature) {
    registerSystemToList(system, signature, _endTickSystems);
}

void SystemManager::registerSystemToList(SystemPtr system,
                                         ComponentSignature& signature,
                                         SystemList& systemsList) {
    std::pair<SystemPtr, ComponentSignature> systemWithSignature
        = std::make_pair(system, signature);
    systemsList.insert(systemWithSignature);
    _isSystemCached[system] = false;
    cacheSystemWithSignature(system, signature);
}

void SystemManager::invalidateSystemCache() {
    for (auto& caches : _isSystemCached) {
        caches.second = false;
    }
    _areSystemsCached = false;
}

void SystemManager::cacheAllSystems() {
    for (const std::pair<SystemPtr, ComponentSignature>& system : _beginTickSystems) {
        if (!_isSystemCached[system.first]) {
            cacheSystemWithSignature(system.first, system.second);
        }
    }
    for (const std::pair<SystemPtr, ComponentSignature>& system : _systems) {
        if (!_isSystemCached[system.first]) {
            cacheSystemWithSignature(system.first, system.second);
        }
    }
    for (const std::pair<SystemPtr, ComponentSignature>& system : _endTickSystems) {
        if (!_isSystemCached[system.first]) {
            cacheSystemWithSignature(system.first, system.second);
        }
    }

    _areSystemsCached = true;
}

void SystemManager::cacheSystemWithSignature(SystemPtr system,
                                             ComponentSignature signature) {
        std::vector<EntityID> matchingEntities
            = _componentMan.getEntitiesWithSignature(signature);
        _systemCache[system] = matchingEntities;
        _isSystemCached[system] = true;
}

void SystemManager::tick() {
    if(!_areSystemsCached) {
        cacheAllSystems();
    }
    for (const std::pair<SystemPtr, ComponentSignature>& system : _beginTickSystems) {
        (*system.first)(_systemCache[system.first], _componentMan, _inputMan, _screenMan);
    }
    for (const std::pair<SystemPtr, ComponentSignature>& system : _systems) {
        (*system.first)(_systemCache[system.first], _componentMan, _inputMan, _screenMan);
    }
    for (const std::pair<SystemPtr, ComponentSignature>& system : _endTickSystems) {
        (*system.first)(_systemCache[system.first], _componentMan, _inputMan, _screenMan);
    }
}
