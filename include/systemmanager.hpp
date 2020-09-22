#pragma once
#include "fwd.hpp"

class SystemManager {
public:
    SystemManager(std::shared_ptr<ComponentManager>);
    void registerSystem(System,
                        ComponentSignature);
    void tick();
private:
    SystemList _systems;
    std::shared_ptr<ComponentManager> _componentMan;
};
