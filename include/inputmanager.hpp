#pragma once
#include <unordered_map>
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

    std::unordered_map<std::string, bool> _keyboardEvents;
    std::unordered_map<std::string, bool> _keyboardState;

};
