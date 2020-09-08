#pragma once
#include "gameobjectbase.hpp"

class Guy : public GameObjectBase {
public:
    Guy();
    virtual void update(const InputManager&,
                        GameEventList&) override;
private:
    bool isRunning;
    std::string runningDirection;
};
