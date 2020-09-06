#include "guy.hpp"
#include "utility.hpp"

namespace {
    const std::string WALKING_RIGHT = "walking_right";
    const std::string WALKING_LEFT = "walking_left";
    const std::string IDLE_DOWN = "idle_down";
}

Guy::Guy() 
	: GameObjectBase("images/guy.bmp", "config/guy.json")
{
        setCurrentAnimationState(WALKING_LEFT);
}
