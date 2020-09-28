#pragma once
#include <algorithm>
#include <unordered_map>
#include <any>
#include "fwd.hpp"

class ComponentManager {
public:
    ComponentManager();
    std::vector<EntityID> getEntitiesWithSignature(ComponentSignature);
    template<typename T> void addComponentForEntity(EntityID, T component);

    template<typename T> std::vector<T>& get();

private:
    std::map<EntityID, ComponentSignature> _entitySignaturesMap;
    std::unordered_map<std::type_index,
                       std::vector<std::byte>> _componentMap;
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

    if (_componentMap.find(insertedType) == _componentMap.end()) {
        _componentMap[insertedType] = std::vector<std::byte>();
    }
    std::vector<T>& typeSafeMap = reinterpret_cast<std::vector<T> &>(_componentMap[insertedType]);
    if (typeSafeMap.size() == 0 || typeSafeMap.size() - 1 < entity) {
        typeSafeMap.resize(std::max<EntityID>(entity * 2, 2));
    }
    typeSafeMap[entity] = component;
}

template<typename T>
std::vector<T>& ComponentManager::get() {
    return reinterpret_cast<std::vector<T> &>(_componentMap[std::type_index(typeid(T))]);
}
