#include "AbstractLevel.h"
#include "../../Settings.h"
#include "../../managers/AssetManager.h"

void AbstractLevel::update(float dt) {
  player->update(dt);
  for (Surface& surface : surfaces) {
    if (player->SurfaceCollide(surface)) {
      break;
    }
  }
}

void AbstractLevel::render() {
  S::Window.clear((player->floor == nullptr) ? sf::Color::White : sf::Color::Red);
  view.setCenter(player->getPosition());
  S::Window.setView(view);
  player->render();
  for (Surface& surface : surfaces) {
    surface.render();
  }

  S::Window.setView(S::Window.getDefaultView());
}

void AbstractLevel::load() {
  player = std::make_shared<AbstractPlayer>();
  player->initialise();
  AssetManager::RegisterTexture("Data/images/FloorTiles.png", 100);
  for (Surface& surface : surfaces) {
    printf("make that texturonie \n");
    surface.initialiseTextures();
  }
}

void AbstractLevel::open() {
  listening_to_inputs = true;
  Resize();
  player->setPosition(player_spawn);
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
  view.setSize(S::Res);
}
