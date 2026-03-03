#include "Egg.h"
#include "../../managers/AssetManager.h"

Egg::Egg(const Vector2f& pos, const Vector2f& vel) {
  setPosition(pos, true);
  velocity = vel;
}
void Egg::update(float dt) {
  velocity += (air_current - velocity) * dt * drag_modifier;
  velocity.y += gravity * dt;
  setPosition(getPosition() + velocity * dt);
}

bool Egg::snapTo(const std::shared_ptr<Collision> &collision) {
  return !(alive = !collision->inRange);
}

bool Egg::snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2) {
  return !(alive = !(c1->inRange && c2->inRange));
}

void Egg::initialise() {
  AbstractCircle::initialise();

  sprite.setTexture(AssetManager::getTexture(110));
  sprite.setOrigin(5, 7);
  radius = 5;
}

void Egg::destroy() {
  alive = false;
}
