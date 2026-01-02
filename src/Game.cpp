#include "Game.h"
#include "birds/menus/MenuLoader.hpp"
#include "managers/ActionManager.h"
#include "managers/MenuManager.h"

bool Game::init() {
  MenuLoader::LoadMenus();
  MenuManager::setMenu("SPSH");


  return true;
}

void Game::update(float dt) {
  MenuManager::update(dt);
  ActionManager::update(dt);
}

void Game::render() {
  window.clear();
  MenuManager::render();
}
