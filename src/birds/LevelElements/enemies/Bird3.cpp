#include "Bird3.h"
#include "../../../managers/AssetManager.h"
#include "../../levels/LevelLibrary.h"

const float Bird3::ELASTIC = 0.75f;
const float Bird3::AIR_ACCELERATION = 1536.0f;
const float Bird3::RADIUS = 12.0f;
const float Bird3::DRAG = 0.5f;

void Bird3::initialise() {
  AbstractBird::initialise();

  AssetManager::RegisterTexture("Data/images/BirdWingSheet2.png", 114);
  wing.setTexture(AssetManager::getTexture(114));

  elasticity = ELASTIC;
  air_acceleration_speed = AIR_ACCELERATION;
  drag_modifier = DRAG;
  hB->r = RADIUS;
}

void Bird3::update(float dt) {
  selfPredictor.QuarryIs(getPosition(), dt);

  velocity += (playerPredictor.f(0.5f) + Vector2f{0.0f, -100.0f} - selfPredictor.f(0.5f)).norm() * air_acceleration_speed * dt;
  velocity += (air_current - velocity) * drag_modifier * dt;
  setPosition(velocity * dt + sprite.getPosition());

  cooldowns(dt);
  considerEgg();
  tickWing(dt);
}

void Bird3::cooldowns(float dt) {
  if (egg_cooldown != 0.0f) {
    egg_cooldown -= dt;
    if (egg_cooldown <= 0.0f) {
      egg_cooldown = 0.0f;
    }
  }
}

AbstractLevelElement* Bird3::makeCopy(const Vector2f& spawn_) const {
  return new Bird3(spawn_);
}
AbstractLevelElement* Bird3::makeCopy() const {
  return new Bird3(spawn_location);
}
