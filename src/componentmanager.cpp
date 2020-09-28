#include "componentmanager.hpp"

ComponentManager::ComponentManager()
    : _entitySignaturesMap(),
      _componentMap()
{}

std::vector<EntityID> ComponentManager::getEntitiesWithSignature(ComponentSignature signature) {
    std::vector<EntityID> returnEntities;
    for (auto& entities : _entitySignaturesMap) {
        if (std::includes(entities.second.begin(), entities.second.end(),
                          signature.begin(), signature.end())) {
            returnEntities.push_back(entities.first);
        }
    }
    return returnEntities;
}
