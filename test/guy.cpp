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

Guy::Guy(Gengine& gengine, Position loc)
{
    EntityID id = gengine.createEntity();
    gengine.giveEntityComponent(id, std::make_shared<GuyRunning>());
    gengine.giveEntityComponent(id, std::make_shared<Position>(loc.x, loc.y));
    gengine.giveEntityComponent(id, std::make_shared<Sprite>("images/guy.bmp", "config/guy.json"));
}

void guyRunningSystem(std::set<EntityID>& entities,
                      std::shared_ptr<ComponentManager> componentMan,
                      std::shared_ptr<InputManager> inputMan,
                      Gengine*)
{
    bool isUpPressed = inputMan->isKeyPressedEvent("W"),
        isLeftPressed = inputMan->isKeyPressedEvent("A"),
        isRightPressed = inputMan->isKeyPressedEvent("D"),
        isDownPressed = inputMan->isKeyPressedEvent("S");
    bool isAnythingOfInterestPressed =
        isDownPressed || isRightPressed || isLeftPressed || isUpPressed;

    if (!isAnythingOfInterestPressed) {
        return;
    }
    std::shared_ptr<std::vector<std::shared_ptr<Sprite>>> entitySprite
        = componentMan->get<Sprite>();

    for (const EntityID& entity : entities) {
        if (isUpPressed) {
            entitySprite->at(entity)->setCurrentAnimationState(WALKING_UP);
        }
        else if (isLeftPressed) {
            entitySprite->at(entity)->setCurrentAnimationState(WALKING_LEFT);
        }
        else if (isDownPressed) {
            entitySprite->at(entity)->setCurrentAnimationState(WALKING_DOWN);
        }
        else if (isRightPressed) {
            entitySprite->at(entity)->setCurrentAnimationState(WALKING_RIGHT);
        }
    }
}
