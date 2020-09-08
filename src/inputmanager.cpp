#include "inputmanager.hpp"
#include <locale>

InputManager::InputManager()
    : _isQuit(false)
{}


void InputManager::addInputEvent(const SDL_Event& e) {
    if (e.type == SDL_QUIT) {
        _isQuit = true;
    }

    switch (e.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        addKeyBoardEvent(e);
        break;
    }

}

void InputManager::clearInputEvents() {
    _keyboardEvents.clear();
}

bool InputManager::isQuit() const {
    return _isQuit;
}

bool InputManager::isKeyPressedEvent(const std::string& keyName) const {
    std::map<std::string, bool>::const_iterator it
        = _keyboardEvents.find(keyName);
    if (it != _keyboardEvents.end()) {
        return it->second;
    }
    return false;
}

void InputManager::addKeyBoardEvent(const SDL_Event& e) {
    std::string keyName = SDL_GetKeyName( e.key.keysym.sym );
    if (e.type == SDL_KEYDOWN) {
        _keyboardEvents[keyName] = true;
        _keyboardState[keyName] = true;
    }
    if (e.type == SDL_KEYUP) {
        _keyboardEvents[keyName] = false;
        _keyboardState[keyName] = false;
    }
}
