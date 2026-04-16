#include "Bird2.h"
#include "../../levels/LevelLibrary.h"
#include "../../managers/AssetManager.h"

const float Bird2::ELASTIC = 0.75f;
const float Bird2::GRAVITY = 384.0f;
const float Bird2::ACCELERATION = 512.0f;
const float Bird2::AIR_ACCELERATION = 2048.0f;
const float Bird2::RADIUS = 12.0f;
const float Bird2::DRAG = 1.5f;

void Bird2::initialise() {
  AbstractBird::initialise();

  elasticity = Bird2::ELASTIC;
  gravity = Bird2::GRAVITY;
  acceleration_speed = Bird2::ACCELERATION;
  air_acceleration_speed = Bird2::AIR_ACCELERATION;
  drag_modifier = Bird2::DRAG;
  hB->r = Bird2::RADIUS;
}

void Bird2::update(float dt) {
  selfPredictor.QuarryIs(getPosition(), dt);

  velocity.y += gravity * dt;
  velocity += (air_current - velocity) * drag_modifier * dt;
  setPosition(velocity * dt + sprite.getPosition());

  cooldowns(dt);
  considerFlap();
  tickWing(dt);
  considerEgg();
}

void Bird2::considerFlap() {
  if (spray == 0 && flap_cooldown == 0.0f && stamina >= 1.0f) {
    flap();
  }
}

void Bird2::cooldowns(float dt) {
  if (flap_cooldown != 0.0f) {
    flap_cooldown -= dt;
    if (flap_cooldown <= 0.0f) {
      flap_cooldown = 0.0f;
    }
  }
  if (egg_cooldown != 0.0f) {
    egg_cooldown -= dt;
    if (egg_cooldown <= 0.0f) {
      egg_cooldown = 0.0f;
    }
  }
  stamina = fminf(stamina + dt, max_stamina);
}

void Bird2::flap() {
  Vector2f cur = getPosition();
  Vector2f tar = playerPredictor.current_position();
  Vector2f pre = selfPredictor.f(0.5f);
  Vector2f tarp = playerPredictor.f(0.5f);

       if (cur.x < tar.x - 50.0f && pre.x < tarp.x + 25.0f)  { setWingRect({0, 54, 29, 27}); wing_direction = { 1, 0}; }
  else if (cur.x > tar.x + 50.0f && pre.x > tarp.x - 25.0f)  { setWingRect({0, 54, 29, 27}); wing_direction = {-1, 0}; }
  else if (cur.y > tar.y - 75.0f && pre.y > tarp.y - 100.0f) { setWingRect({0, 27, 29, 27}); }
  else { return; }
  stamina -= 1.0f;
  flap_cooldown = flap_max_cooldown;
  anim_cooldown = 0.125f;
}

AbstractLevelElement* Bird2::makeCopy(const Vector2f& spawn_) const {
  return new Bird2(spawn_);
}
AbstractLevelElement* Bird2::makeCopy() const {
  return new Bird2(spawn_location);
}
