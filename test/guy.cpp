#include <cstdlib>
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
    gengine.giveEntityComponent(id, std::make_shared<Destination>(loc.x, loc.y, 1));
    gengine.giveEntityComponent(id, std::make_shared<Sprite>("images/guy.bmp", "config/guy.json"));
}

void guyRunningSystem(std::set<EntityID>& entities,
                      std::shared_ptr<ComponentManager> componentMan,
                      std::shared_ptr<InputManager> inputMan,
                      std::shared_ptr<ScreenManager>)
{
    static int wanderTicks = 60;
    static int movementTicks = 3;
    std::shared_ptr<std::vector<std::shared_ptr<Sprite>>> entitySprite
        = componentMan->get<Sprite>();
    std::shared_ptr<std::vector<std::shared_ptr<Position>>> entityPos
        = componentMan->get<Position>();
    std::shared_ptr<std::vector<std::shared_ptr<Destination>>> entityDest
        = componentMan->get<Destination>();


    for (const EntityID& entity : entities) {
        std::shared_ptr<Position> curr = (*entityPos)[entity];
        std::shared_ptr<Destination> currDest = (*entityDest)[entity];
        long xdelta = curr->x - currDest->dest.x;
        long ydelta = curr->y - currDest->dest.y;
        if (movementTicks == 0) {
            if (curr->x < currDest->dest.x) {
                curr->x += currDest->velocity;;
            }
            else if (curr->x > currDest->dest.x) {
                curr->x -= currDest->velocity;
            }

            if (curr->y < currDest->dest.y) {
                curr->y += currDest->velocity;
            }
            else if (curr->y > currDest->dest.y) {
                curr->y -= currDest->velocity;
            }

            if (xdelta > 0 && xdelta > ydelta) {
                entitySprite->at(entity)->setCurrentAnimationState(WALKING_LEFT);
            }
            else if (xdelta < 0 && xdelta > ydelta) {
                entitySprite->at(entity)->setCurrentAnimationState(WALKING_RIGHT);
            }
            else if (ydelta < 0 && ydelta > xdelta) {
                entitySprite->at(entity)->setCurrentAnimationState(WALKING_DOWN);
            }
            else if (ydelta > 0 && ydelta > xdelta) {
                entitySprite->at(entity)->setCurrentAnimationState(WALKING_UP);
            }
        }

        if (wanderTicks == 0 && (std::rand() % 10) > 4) {
            currDest->dest.x = curr->x + ((std::rand() % 1000) - (std::rand() % 1000));
            currDest->dest.y = curr->y + ((std::rand() % 1000) - (std::rand() % 1000));
        }
    }

    if (movementTicks == 0) {
        movementTicks = 1;
    }
    else {
        --movementTicks;
    }
    if (wanderTicks == 0) {
        wanderTicks = 120;
    }
    else {
        --wanderTicks;
    }
}
