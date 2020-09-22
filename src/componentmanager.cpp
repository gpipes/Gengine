#include "componentmanager.hpp"

std::set<EntityID> ComponentManager::getEntitiesWithSignature(ComponentSignature signature) {
    std::set<EntityID> returnEntities;
    for (auto& entities : _entitySignaturesMap) {
        if (std::includes(entities.second.begin(), entities.second.end(),
                          signature.begin(), signature.end())) {
            returnEntities.insert(entities.first);
        }
    }
    return returnEntities;
}
