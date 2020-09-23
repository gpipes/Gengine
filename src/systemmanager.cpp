#include "systemmanager.hpp"
#include "componentmanager.hpp"

SystemManager::SystemManager(std::shared_ptr<ComponentManager> componentMan)
    : _componentMan(componentMan)
{}

void SystemManager::registerSystem(std::shared_ptr<System> system,
                                   ComponentSignature signature) {
    registerSystemToList(system, signature, _systems);
}

void SystemManager::registerBeginTickSystem(std::shared_ptr<System> system,
                                            ComponentSignature signature) {
    registerSystemToList(system, signature, _beginTickSystems);
}

void SystemManager::registerEndTickSystem(std::shared_ptr<System> system,
                                           ComponentSignature signature) {
    registerSystemToList(system, signature, _endTickSystems);
}

void SystemManager::registerSystemToList(std::shared_ptr<System> system,
                                         ComponentSignature& signature,
                                         SystemList& systemsList) {
    std::pair<std::shared_ptr<System>, ComponentSignature> systemWithSignature
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
    for (const std::pair<std::shared_ptr<System>, ComponentSignature>& system : _beginTickSystems) {
        if (!_isSystemCached[system.first]) {
            cacheSystemWithSignature(system.first, system.second);
        }
    }
    for (const std::pair<std::shared_ptr<System>, ComponentSignature>& system : _systems) {
        if (!_isSystemCached[system.first]) {
            cacheSystemWithSignature(system.first, system.second);
        }
    }
    for (const std::pair<std::shared_ptr<System>, ComponentSignature>& system : _endTickSystems) {
        if (!_isSystemCached[system.first]) {
            cacheSystemWithSignature(system.first, system.second);
        }
    }

    _areSystemsCached = true;
}

void SystemManager::cacheSystemWithSignature(std::shared_ptr<System> system,
                                             ComponentSignature signature) {
        std::set<EntityID> matchingEntities
            = _componentMan->getEntitiesWithSignature(signature);
        _systemCache[system] = matchingEntities;
        _isSystemCached[system] = true;
}

void SystemManager::tick() {
    if(!_areSystemsCached) {
        cacheAllSystems();
    }
    for (const std::pair<std::shared_ptr<System>, ComponentSignature>& system : _beginTickSystems) {
        (*system.first)(_systemCache[system.first], _componentMan);
    }
    for (const std::pair<std::shared_ptr<System>, ComponentSignature>& system : _systems) {
        (*system.first)(_systemCache[system.first], _componentMan);
    }
    for (const std::pair<std::shared_ptr<System>, ComponentSignature>& system : _endTickSystems) {
        (*system.first)(_systemCache[system.first], _componentMan);
    }
}
