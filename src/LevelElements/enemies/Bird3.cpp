#include "Bird3.h"
#include "../../levels/LevelLibrary.h"
#include "../../managers/AssetManager.h"

const float Bird3::ELASTIC = 0.75f;
const float Bird3::AIR_ACCELERATION = 3072.0f;
const float Bird3::RADIUS = 12.0f;
const float Bird3::DRAG = 0.25f;

void Bird3::initialise() {
  AbstractBird::initialise();

  AssetManager::RegisterTexture("Data/images/BirdWingSheet2.png", 114);
  wing.setTexture(AssetManager::getTexture(114));

  elasticity = Bird3::ELASTIC;
  air_acceleration_speed = Bird3::AIR_ACCELERATION;
  drag_modifier = Bird3::DRAG;
  hB->r = Bird3::RADIUS;
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

void Bird3::onHitSurface(const std::shared_ptr<Collision>& collision) {
  snapTo(collision);
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
