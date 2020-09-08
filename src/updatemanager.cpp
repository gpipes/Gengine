#include "updatemanager.hpp"
#include "gameobjectbase.hpp"

void UpdateManager::updateWorld(const GameObjectList& world,
                                const InputManager& inputMan) {
    GameEventList totalEvents;
    for (GameObjectPtr gameObject : world) {
        GameEventList eventsThisUpdate;
        gameObject->update(inputMan, eventsThisUpdate);
        totalEvents.insert(totalEvents.end(), eventsThisUpdate.begin(),
                           eventsThisUpdate.end());
    }
}
