#pragma once
#include <algorithm>
#include <unordered_map>
#include <any>
#include "fwd.hpp"

class ComponentManager {
public:
    ComponentManager();
    std::set<EntityID> getEntitiesWithSignature(ComponentSignature);
    template<typename T> std::shared_ptr<T> getComponentForEntity(EntityID);
    template<typename T> void addComponentForEntity(EntityID, std::shared_ptr<T> component);

    template<typename T>
    std::shared_ptr<
        std::vector<std::shared_ptr<T>>> get();

private:
    std::map<EntityID, ComponentSignature> _entitySignaturesMap;
    std::unordered_map<std::type_index,
                       std::shared_ptr<std::vector<std::shared_ptr<void>>>> _componentMap;
};

template<typename T>
void ComponentManager::addComponentForEntity(EntityID entity, std::shared_ptr<T> component) {
    ComponentSignature existingSignature;
    std::type_index insertedType = std::type_index(typeid(T));

    if (_entitySignaturesMap.find(entity) != _entitySignaturesMap.end()) {
        existingSignature = _entitySignaturesMap[entity];
    }

    existingSignature.insert(insertedType);
    _entitySignaturesMap[entity] = existingSignature;

    if (_componentMap.find(insertedType) == _componentMap.end()) {
        _componentMap[insertedType]
            = std::make_shared<std::vector<std::shared_ptr<void>>>();
        _componentMap[insertedType]->resize(std::max<EntityID>(entity * 2, 2));
    } else if ((_componentMap[insertedType]->size()-1) < entity) {
        _componentMap[insertedType]->resize(entity * 2);
    }
    (*_componentMap[insertedType])[entity] = component;
}

template<typename T>
std::shared_ptr<T> ComponentManager::getComponentForEntity(EntityID id)
{
    return std::reinterpret_pointer_cast<T>(
        _componentMap.at(std::type_index(typeid(T)))->at(id)
        );
}

template<typename T>
std::shared_ptr<std::vector<std::shared_ptr<T>>> ComponentManager::get() {
    return std::reinterpret_pointer_cast<std::vector<std::shared_ptr<T>>>
        (_componentMap[std::type_index(typeid(T))]);
}
