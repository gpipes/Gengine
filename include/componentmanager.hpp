#pragma once
#include <algorithm>
#include <unordered_map>
#include <any>
#include "fwd.hpp"

class ComponentManager {
public:
    ComponentManager();
    std::set<EntityID> getEntitiesWithSignature(ComponentSignature);
    template<typename T> T& getComponentForEntity(EntityID);
    template<typename T> void addComponentForEntity(EntityID, T);

    template<typename T>
    std::vector<std::pair<EntityID, T*>> getComponentsForSignature(ComponentSignature);

private:
    std::map<EntityID, ComponentSignature> _entitySignaturesMap;
    std::unordered_map<std::type_index,
                       std::unordered_map<EntityID, std::any>> _componentMap;
};

template<typename T>
void ComponentManager::addComponentForEntity(EntityID entity, T component) {
    ComponentSignature existingSignature;
    std::type_index insertedType = std::type_index(typeid(T));

    if (_entitySignaturesMap.find(entity) != _entitySignaturesMap.end()) {
        existingSignature = _entitySignaturesMap[entity];
    }

    existingSignature.insert(insertedType);
    _entitySignaturesMap[entity] = existingSignature;

    _componentMap[insertedType][entity] = component;
}

template<typename T>
T& ComponentManager::getComponentForEntity(EntityID id)
{
    return std::any_cast<T&>(
        _componentMap.at(std::type_index(typeid(T))).at(id)
        );
}
