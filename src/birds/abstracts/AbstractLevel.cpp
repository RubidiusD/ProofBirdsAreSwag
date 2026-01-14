#include "AbstractLevel.h"
#include "../../managers/AssetManager.h"
#include "../../managers/InputManager.h"

void AbstractLevel::update(float dt) {
  // update wind
  for (std::shared_ptr<Wind>& wind : winds) {
    wind->update(dt);
  }

  // update player
  player->applyWind(winds);
  player->update(dt);
  for (Surface& surface : surfaces) {
    if (player->SurfaceCollide(surface)) {
      break;
    }
  }

  // update elements
  for (long index = 0; index != elements.size(); index ++) {
    elements[index]->applyWind(winds);
    elements[index]->update(dt);
    if (!elements[index]->alive) {
      for (long index2 = index + 1; index2 != elements.size(); index2 ++) {
        elements[index2 - 1] = elements[index2];
      }
      elements.pop_back();
      index --;
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
  for (std::shared_ptr<AbstractLevelElement>& element : elements) {
    element->render();
  }
}

void AbstractLevel::load() {
  InputManager::subscribe(this);
  if (player != nullptr) {
    player->initialise();
  }
  AssetManager::RegisterTexture("Data/images/FloorTiles.png", 100);
  AssetManager::RegisterTexture("Data/images/Particles.png", 101);
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

void AbstractLevel::Move(const sf::Vector2f& vector) {
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

void AbstractLevel::addElement(AbstractLevelElement *element) {
  elements.emplace_back(element);
  element->initialise();
}
void AbstractLevel::Look(const sf::Vector2f &vector) {
  player->Look(vector);
}
