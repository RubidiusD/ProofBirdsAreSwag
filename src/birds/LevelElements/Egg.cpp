#include "Egg.h"
#include "../../managers/AssetManager.h"
#include "../levels/LevelLibrary.h"
#include "EggParticle.h"

Egg::Egg(const Vector2f& pos, const Vector2f& vel) : AbstractCircle(pos) {
  velocity = vel;
}
void Egg::spawn() { alive = false; }

void Egg::update(float dt) {
  velocity += (air_current - velocity) * dt * drag_modifier;
  velocity.y += gravity * dt;
  sprite.setRotation(atan2f(velocity.y, velocity.x) * 180.0f / 3.14159265358979f - 90.0f);
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

  hB->r = 5;

  setPosition(spawn_location);
  drag_modifier = 0.5f;
}

void Egg::remove() {
  for (int index = 0; index != 6; index ++) {
    LevelLibrary::current_level->addElement(new EggParticle(getPosition(), Vector2f(M::Randf(-1.0f, 1.0f), -1.0f) * 140.0f, index));
  }
}
