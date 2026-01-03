#include "Game.h"
#include "../managers/ActionManager.h"
#include "../managers/MenuManager.h"
#include "../managers/Settings.h"
#include "menus/MenuLoader.hpp"

bool Game::init() {
  MenuLoader::LoadMenus();
  MenuManager::setMenu("SPSH");


  return true;
}

void Game::update(float dt) {
  MenuManager::update(dt);
  ActionManager::update(dt);
  if (current_level != nullptr) {
    current_level->update(dt);
  }
}

void Game::render() {
  window.clear();
  MenuManager::render();
  if (current_level != nullptr) {
    current_level->render();
  }
}

void Game::manageInputs(sf::Event event) {
  if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
    S::Window.close();
    return;
  }

  if (MenuManager::manageInputs(event)) {
    return;
  }
}
