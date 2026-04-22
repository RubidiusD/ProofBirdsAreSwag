#include "Game.h"
#include "managers/ActionManager.h"
#include "managers/MenuManager.h"
#include "managers/SoundManager.h"

bool Game::init() {
  SoundManager::LoadSounds();

  return true;
}

void Game::update(float dt) {
  ActionManager::update(dt);
  if (!MenuManager::update(dt) && level != nullptr) {
    level->update(dt);
  }
  SoundManager::update();
}

void Game::render() {
  window.clear();
  if (level != nullptr) {
    level->render();
  }
  MenuManager::render();
}
