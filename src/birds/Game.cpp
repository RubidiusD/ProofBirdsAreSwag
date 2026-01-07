#include "Game.h"
#include "../managers/ActionManager.h"
#include "../managers/MenuManager.h"

bool Game::init() {

  return true;
}

void Game::update(float dt) {
  MenuManager::update(dt);
  ActionManager::update(dt);
  if (level != nullptr) {
    level->update(dt);
  }
}

void Game::render() {
  window.clear();
  MenuManager::render();
  if (level != nullptr) {
    level->render();
  }
}

