#include "guy.hpp"
#include "utility.hpp"
#include "gengine.hpp"

namespace {
    const std::string WALKING_RIGHT = "walking_right";
    const std::string WALKING_LEFT = "walking_left";
    const std::string WALKING_UP = "walking_up";
    const std::string WALKING_DOWN = "walking_down";
    const std::string IDLE_DOWN = "idle_down";
}

Guy::Guy(Gengine& gengine)
{
    EntityID id = gengine.createEntity();
    gengine.giveEntityComponent(id, Position(0,0));
    gengine.giveEntityComponent(id, Sprite("images/guy.bmp", "config/guy.json"));
}

// void Guy::update(const InputManager& inputMan, GameEventList&) {
//     if (inputMan.isKeyPressedEvent("W")) {
//         setCurrentAnimationState(WALKING_UP);
//         runningDirection = WALKING_UP;
//     }
//     if (inputMan.isKeyPressedEvent("A")) {
//         setCurrentAnimationState(WALKING_LEFT);
//         runningDirection = WALKING_LEFT;
//     }
//     if (inputMan.isKeyPressedEvent("S")) {
//         setCurrentAnimationState(WALKING_DOWN);
//         runningDirection = WALKING_DOWN;
//     }
//     if (inputMan.isKeyPressedEvent("D")) {
//         setCurrentAnimationState(WALKING_RIGHT);
//         runningDirection = WALKING_RIGHT;
//     }
// }
