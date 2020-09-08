#pragma once
#include <vector>
#include <memory>
#include "Fwd.hpp"
#include "inputmanager.hpp"

class UpdateManager {
public:
    void updateWorld(const GameObjectList& gameWorld,
                     const InputManager& inputMan);
private:
};
