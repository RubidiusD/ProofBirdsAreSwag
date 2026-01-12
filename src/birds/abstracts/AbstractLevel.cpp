#include "AbstractLevel.h"
#include "../../Settings.h"
#include "../../managers/AssetManager.h"
#include "../../managers/InputManager.h"

void AbstractLevel::update(float dt) {
  for (std::shared_ptr<Wind>& wind : winds) {
    wind->update(dt);
  }
  player->applyWind(winds);
  player->update(dt);
  for (Surface& surface : surfaces) {
    if (player->SurfaceCollide(surface)) {
      break;
    }
  }
}

void AbstractLevel::render() {
  view.setCenter(player->getPosition());
  S::Window.clear(sf::Color::White);
  S::Window.setView(view);
  player->render();
  for (Surface& surface : surfaces) {
    surface.render();
  }
}

void AbstractLevel::load() {
  InputManager::subscribe(this);
  player = std::make_shared<AbstractPlayer>();
  player->initialise();
  AssetManager::RegisterTexture("Data/images/FloorTiles.png", 100);
  for (Surface& surface : surfaces) {
    printf("make that texturonie \n");
    surface.initialiseTextures();
  }
  view.setSize(960, 540);
}

void AbstractLevel::open() {
  listening_to_inputs = true;
  Resize();
  player->setPosition(player_spawn, true);
}

void AbstractLevel::close() {
  listening_to_inputs = false;
}

void AbstractLevel::unload() {
  surfaces.clear();
  player = nullptr;
}

void AbstractLevel::Move(sf::Vector2f vector) {
  if (player != nullptr) {
    player->Move(vector);
  }
}

void AbstractLevel::Select(bool down) {
  if (player != nullptr) {
    player->Jump(down);
  }
}

void AbstractLevel::Resize() {
  view.setSize(960, 540);
  float p = 16 * S::ScreenSize.y / 9 / S::ScreenSize.x;
  if (1 > p) {
    view.setViewport({(1 - p) / 2, 0, p, 1});
  }
  else if (1 < p){
    view.setViewport({0, (1 - 1/p) / 2, 1, 1/p});
  }
  else {
    view.setViewport({0, 0, 1, 1});
  }
}
