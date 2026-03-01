#include "AbstractLevel.h"
#include "../../MathLib.h"
#include "../../managers/AssetManager.h"
#include "../../managers/InputManager.h"
#include "../../managers/MenuManager.h"
#include "../LevelElements/Particle.h"

void AbstractLevel::update(float dt) {
  // update wind
  for (std::shared_ptr<AbstractWind>& wind : winds) {
    wind->update(dt);
  }
  windParticles();

  // update player
  player->applyWind(winds);
  player->update(dt);
  for (Surface& surface : surfaces) {
    if (player->surfaceCollide(surface)) {
      break;
    }
  }

  for (PlayerListener*& listener : listeners) {
    listener->QuarryIs(player->getPosition(), dt);
  }

  // update elements
  for (long index = 0; index != elements.size(); index ++) {
    elements[index]->applyWind(winds);
    elements[index]->update(dt);

    for (Surface& surface : surfaces) {
      if (elements[index]->surfaceCollide(surface)) {
        break;
      }
    }

    if (!elements[index]->alive) {
      elements[index]->remove();
      for (long index2 = index + 1; index2 != elements.size(); index2 ++) {
        elements[index2 - 1] = elements[index2];
      }
      elements.pop_back();
      index --;
    }
  }

  clearOut();
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
  AssetManager::RegisterTexture("Data/images/Particles3.png", 101);
  for (Surface& surface : surfaces) {
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

void AbstractLevel::Move(const Vector2f& vector) {
  if (player != nullptr) {
    player->Move(vector);
  }
}

void AbstractLevel::Pause(bool down) {
  if (down) {
    MenuManager::setMenu("PAUS");
  }
  listening_to_inputs = !down;
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

void AbstractLevel::addListener(PlayerListener *listener) {
  listeners.emplace_back(listener);
}

void AbstractLevel::addEgg(const Vector2f& pos, const Vector2f& vel) {
  eggs.emplace_back(new Egg(pos, vel));
  elements.emplace_back(eggs.back());
  eggs.back()->initialise();
}

void AbstractLevel::Look(const Vector2f &vector) {
  player->Look(vector);
}

void AbstractLevel::spawnParticle(const Vector2f& position, const Vector2f& velocity) {
  addElement(new Particle(position, velocity, 0.3f));
}

void AbstractLevel::spawnParticle(const Vector2f& position, const Vector2f& velocity, float duration) {
  addElement(new Particle(position, velocity, duration));
}

void AbstractLevel::spawnParticle(unsigned int number, const Vector2f& position, const Vector2f& direction) {
  if (M::lengthSQ(direction) > 100) {
    for (unsigned index = 0; index != number; index ++) {
      spawnParticle(position, direction * Vector2f(1, M::Randf(-1, 1)).norm());
    }
  }
}

void AbstractLevel::clearOut() {
  for (int index = 0; index != eggs.size(); index ++) {
    if (!eggs[index]->alive) {
      for (int i = index + 1; i != eggs.size(); i ++) {
        eggs[i - 1] = eggs[i];
      }
      eggs.pop_back();
      index --;
    }
  }
}

void AbstractLevel::removeListener(PlayerListener& listener) {
  for (int index = 0; index != listeners.size(); index ++) {
    if (listeners[index] == &listener) {
      for (int i = index + 1; i != listeners.size(); i ++) {
        listeners[i - 1] = listeners[i];
      }
      listeners.pop_back();
      return;
    }
  }
}

void AbstractLevel::windParticles() {
  Vector2f TopLeft  = windAt(S::Window.mapPixelToCoords({0, 0}, view));
  Vector2f TopRight = windAt(S::Window.mapPixelToCoords({(int)S::ScreenSize.x, 0}, view));
  Vector2f BotLeft  = windAt(S::Window.mapPixelToCoords({0, (int)S::ScreenSize.y}, view));
  Vector2f BotRight = windAt(S::Window.mapPixelToCoords({(int)S::ScreenSize.x, (int)S::ScreenSize.y}, view));
  bool inTL = (TopLeft.x > 0.0f && TopLeft.y > 0.0f);
  bool inTR = (TopRight.x < 0.0f && TopRight.y > 0.0f);
  bool inBL = (BotLeft.x > 0.0f && BotLeft.y < 0.0f);
  bool inBR = (BotRight.x < 0.0f && BotRight.y < 0.0f);

  // top edge
  if (inTL || inTR) {
    Vector2f point = S::Window.mapPixelToCoords({(int)M::Rand(0, (unsigned)S::ScreenSize.x), 0}, view);
    spawnParticle(point, windAt(point), 10.0f);
  }

  // left edge
  if (inTL || inBL) {
    Vector2f point = S::Window.mapPixelToCoords({0, (int)M::Rand(0, (unsigned)S::ScreenSize.y)}, view);
    spawnParticle(point, windAt(point), 10.0f);
  }

  // right edge
  if (inTR || inBR) {
    Vector2f point = S::Window.mapPixelToCoords({(int)S::ScreenSize.x, (int)M::Rand(0, (unsigned)S::ScreenSize.y)}, view);
    spawnParticle(point, windAt(point), 10.0f);
  }

  // bottom edge
  if (inBL || inBR) {
    Vector2f point = S::Window.mapPixelToCoords({(int)M::Rand(0, (unsigned)S::ScreenSize.x), (int)S::ScreenSize.y}, view);
    spawnParticle(point, windAt(point), 10.0f);
  }
}

Vector2f AbstractLevel::windAt(const Vector2f &point) const {
  Vector2f total;
  for (const std::shared_ptr<AbstractWind>& wind : winds) {
    if (wind->isInside(point, 0)) {
      total += wind->velocity;
    }
  }
  return total;
}
