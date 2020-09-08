#pragma once
#include <map>
#include <string>
#include <SDL.h>

class InputManager {
public:
    InputManager();
    void addInputEvent(const SDL_Event& e);
    void clearInputEvents();
    bool isQuit() const;
    bool isKeyPressedEvent(const std::string&) const;
private:
    void addKeyBoardEvent(const SDL_Event& e);
    bool _isQuit;

    std::map<std::string, bool> _keyboardEvents;
    std::map<std::string, bool> _keyboardState;

};
