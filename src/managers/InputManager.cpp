#include "InputManager.h"
#include "MenuManager.h"
#include "Settings.h"

void InputManager::manageInputs(sf::Event event) {
  if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
    S::Window.close();
    return;
  }

  if (MenuManager::manageInputs(event)) {
    return;
  }
}
