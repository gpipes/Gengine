#pragma once
#include "gameobjectbase.hpp"

class Guy : public GameObjectBase {
public:
	enum States {IDLE, WALKING_RIGHT, WALKING_DOWN};
	Guy();
};