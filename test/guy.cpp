#include <cstdlib>
#include "guy.hpp"
#include "utility.hpp"
#include "gengine.hpp"

namespace {
    const int WALKING_RIGHT = 1;
    const int WALKING_LEFT = 2;
    const int WALKING_UP = 3;
    const int WALKING_DOWN = 4;
    const int IDLE_DOWN = 0;
}

Guy::Guy(Gengine& gengine, Position loc)
{
    EntityID id = gengine.createEntity();
    gengine.giveEntityComponent<GuyRunning>(id);
    gengine.giveEntityComponent<Position>(id, loc.x, loc.y);
    gengine.giveEntityComponent<Destination>(id, loc.x, loc.y, 1);
    gengine.giveEntityComponent<Sprite>(id, "images/guy.bmp", "config/guy.json");
}

void guyRunningSystem(const std::vector<EntityID>& entities,
                      ComponentManager& componentMan,
                      InputManager&,
                      ScreenManager&)
{
    static int wanderTicks = 60;
    static int movementTicks = 3;
    std::vector<Sprite>& entitySprite = componentMan.get<Sprite>();
    std::vector<Position>& entityPos = componentMan.get<Position>();
    std::vector<Destination>& entityDest = componentMan.get<Destination>();


    for (const EntityID& entity : entities) {
        Position& curr = entityPos[entity];
        Destination& currDest = entityDest[entity];
        long xdelta = curr.x - currDest.dest.x;
        long ydelta = curr.y - currDest.dest.y;
        if (movementTicks == 0) {
            if (curr.x < currDest.dest.x) {
                curr.x += currDest.velocity;;
            }
            else if (curr.x > currDest.dest.x) {
                curr.x -= currDest.velocity;
            }

            if (curr.y < currDest.dest.y) {
                curr.y += currDest.velocity;
            }
            else if (curr.y > currDest.dest.y) {
                curr.y -= currDest.velocity;
            }

            if (xdelta > 0 && xdelta > ydelta) {
                entitySprite[entity].setCurrentAnimationState(WALKING_LEFT);
            }
            else if (xdelta < 0 && xdelta > ydelta) {
                entitySprite[entity].setCurrentAnimationState(WALKING_RIGHT);
            }
            else if (ydelta < 0 && ydelta > xdelta) {
                entitySprite[entity].setCurrentAnimationState(WALKING_DOWN);
            }
            else if (ydelta > 0 && ydelta > xdelta) {
                entitySprite[entity].setCurrentAnimationState(WALKING_UP);
            }
        }

        if (wanderTicks == 0 && (std::rand() % 10) > 4) {
            currDest.dest.x = curr.x + ((std::rand() % 1000) - (std::rand() % 1000));
            currDest.dest.y = curr.y + ((std::rand() % 1000) - (std::rand() % 1000));
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
