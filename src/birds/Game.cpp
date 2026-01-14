#include "Game.h"
#include "../managers/ActionManager.h"
#include "../managers/MenuManager.h"

bool Game::init() {

  return true;
}

void Game::update(float dt) {
  ActionManager::update(dt);
  if (!MenuManager::update(dt) && level != nullptr) {
    level->update(dt);
  }
}

void Game::render() {
  window.clear();
  if (level != nullptr) {
    level->render();
  }
  MenuManager::render();
}

