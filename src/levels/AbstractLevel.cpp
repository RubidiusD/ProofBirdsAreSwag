#include "AbstractLevel.h"
#include "../LevelElements/fx/Particle.h"
#include "../MathLib.h"
#include "../managers/AssetManager.h"
#include "../managers/InputManager.h"
#include "../managers/MenuManager.h"
#include "../menus/ResultsMenu.h"

void AbstractLevel::update(float dt) {
  // update wind
  for (std::shared_ptr<AbstractWind>& wind : winds) {
    wind->update(dt);
  }
  windParticles(dt);

  // update player
  player->applyWind(winds);
  player->update(dt);
  if (player->collidesSurface()) {
    for (Surface& surface : surfaces) {
      if (player->surfaceCollide(surface)) {
        break;
      }
    }
  }

  for (PlayerListener*& listener : listeners) {
    listener->QuarryIs(player->getPosition(), dt);
  }

  // update elements
  updateElements(dt);

  for (ProgressTrigger& trigger : checkpoints) {
    trigger.update(dt);
  }

  chapter.duration += dt;

  if (chapter.first_egg != -1.0f) {
    chapter.first_egg += dt;
    if (chapter.second_egg != -1.0f) {
      chapter.second_egg += dt;
    }
  }
}

void AbstractLevel::updateElements(float dt) {
  for (long index = 0; index != elements.size(); index ++) {
    elements[index]->applyWind(winds);
    elements[index]->update(dt);

    if (elements[index]->alive && elements[index]->collidesSurface()) {
      for (Surface& surface : surfaces) {
        if (elements[index]->surfaceCollide(surface)) {
          break;
        }
      }
    }

    if (listening_to_inputs && elements[index]->alive && elements[index]->collidesPlayer() && elements[index]->circleCollide(player->hB)) {
      elements[index]->onHitPlayer();
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
}

void AbstractLevel::render() {
  view.setCenter(player->getPosition() + Vector2f{0.0f, -64.0f});
  S::Window.clear(sf::Color::White);
  S::Window.setView(view);
  player->render();
  for (Surface& surface : surfaces) {
    surface.render();
  }
  for (std::shared_ptr<AbstractLevelElement>& element : elements) {
    element->render();
  }
  S::Window.setView(S::UI_View);
  player->renderUI();
}

void AbstractLevel::load() {
  InputManager::subscribe(this);
  if (player != nullptr) {
    player->initialise();
  }
  AssetManager::RegisterTexture("Data/images/FloorTiles.png", 100);
  AssetManager::RegisterTexture("Data/images/Particles3.png", 101);
  for (Surface& surface : surfaces) {
    surface.initialiseTextures(particle_rate);
  }
  view.setSize(960, 540);
  isLoaded = true;
}

void AbstractLevel::open() {
  listening_to_inputs = true;
  Resize();
  chapter.reset();
  player->spawn();
  for (Surface& surface : surfaces) {
    surface.active = surface.default_active;
  }
  bool incrementing;
  for (int index = elements.size() - 1; index != -1; index -= incrementing ? 1 : 0) {
    incrementing = true;
    if (elements[index]->destroy_on_load) {
      elements[index]->remove();
      for (unsigned i = index + 1; i != elements.size(); i ++) {
        elements[i - 1] = elements[i];
      }
      elements.pop_back();
      incrementing = false;
    }
    else {
      elements[index]->spawn();
    }
  }
  for (ProgressTrigger& t : checkpoints) {
    t.spawn();
  }
}

void AbstractLevel::close() {
  listening_to_inputs = false;
//  ResultsMenu::instance->AddAttempt(timer, checkpoints.size() + 1);
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

void AbstractLevel::Look(const Vector2f& vector) {
  player->Look(vector);
}

void AbstractLevel::Point(const Vector2f &vector) {
  player->Point(vector);
}

void AbstractLevel::spawnParticle(const Vector2f& position, const Vector2f& velocity) {
  addElement(new Particle(position, velocity));
}

void AbstractLevel::spawnParticle(unsigned int number, const Vector2f& position, const Vector2f& direction) {
  if (M::lengthSQ(direction) > 100) {
    for (unsigned index = 0; index != number; index ++) {
      spawnParticle(position, direction.rotate(Vector2f(1, M::Randf(-1, 1)).norm()));
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

void AbstractLevel::windParticles(float dt) {
  for (Surface& surface : surfaces) {
    if (!surface.active)
      continue;
    for (Edge& edge : surface.edges) {
      edge.wind_cooldown -= dt;
      if (edge.wind_cooldown <= 0.0f) {
        edge.wind_cooldown = particle_rate;
        Vector2f wind1 = windAt(edge.point);
        Vector2f wind2 = windAt(edge.next->point);

        if (wind1.dot(edge.norm) >= 0 || wind2.dot(edge.norm) >= 0) {
          spawnParticle(edge.point + edge.dire * M::Randf(0, 1), (wind1 + wind2) * 0.05f);
        }
      }
    }
  }
}

Vector2f AbstractLevel::windAt(const Vector2f& point) const {
  Vector2f total;
  for (const std::shared_ptr<AbstractWind>& wind : winds) {
    if (wind->isInside(point)) {
      total += wind->velocity;
    }
  }
  return total;
}

void AbstractLevel::hurtPlayer(const Vector2f& source) {
  if (chapter.first_egg == -1.0f) {
    chapter.first_egg = 0.0f;
  }
  else if (chapter.second_egg == -1.0f) {
    chapter.second_egg = 0.0f;
  }

//  if (player->hurt(source)) {
//    publishProgress(DIED);
    //  printf("publish progress is fine \n");
//    open();
    //  printf("open is also fine \n");
//  }
}

std::shared_ptr<AbstractPlayer> AbstractLevel::getPlayer() {
  return player;
}

void AbstractLevel::publishProgress(ProgressType type) {
  chapter.type = type;
  ResultsMenu::instance->AddChapter(chapter);
  chapter.reset();
}

void AbstractLevel::addCheckpointAt(const Vector2f& pos1, const Vector2f& pos2) {
  checkpoints.emplace_back(chapter.progress, pos1, pos2, checkpoints.size() + 1); // chapter.progress here is a reference lol
}
