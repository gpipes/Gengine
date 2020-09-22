#include "systemmanager.hpp"
#include "componentmanager.hpp"

SystemManager::SystemManager(std::shared_ptr<ComponentManager> componentMan)
    : _componentMan(componentMan)
{}

void SystemManager::registerSystem(System system, ComponentSignature signature) {
    _systems.push_back(std::make_pair(system, signature));
}

void SystemManager::tick() {
    for (const std::pair<System, ComponentSignature>& system : _systems) {
        std::set<EntityID> matchingEntities;
        matchingEntities = _componentMan->getEntitiesWithSignature(system.second);
        system.first(matchingEntities, _componentMan);
    }
}
