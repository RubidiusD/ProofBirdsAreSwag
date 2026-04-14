#include "Bird4.h"

const float Bird4::ELASTIC = 0.25f;
const float Bird4::GRAVITY = 384.0f;
const float Bird4::ACCELERATION = 512.0f;
const float Bird4::AIR_ACCELERATION = 2048.0f;
const float Bird4::RADIUS = 12.0f;

void Bird4::initialise() {
  AbstractBird::initialise();

  elasticity = ELASTIC;
  gravity = GRAVITY;
  acceleration_speed = ACCELERATION;
  air_acceleration_speed = AIR_ACCELERATION;
  hB->r = RADIUS;
  max_stamina = 5.0f;
}

void Bird4::update(float dt) {
  selfPredictor.QuarryIs(getPosition(), dt);

  tiltWing(dt);
  soar(dt);
  setPosition(velocity * dt + sprite.getPosition());

  cooldowns(dt);
  considerFlap();
  tickWing(dt);
  considerEgg();
}

void Bird4::tiltWing(float dt) {
  if (playerPredictor.getPrecision() < 2) {
    return;
  }
  Vector2f wing_normal = wing_direction.i();
  Vector2f intent = playerPredictor.f(0.5f) + Vector2f{0.0f, -100.0f} - selfPredictor.f(0.5f);
  float strength = intent.dot(wing_normal);
  wing_direction += wing_normal * strength * dt * 0.00025f;
  wing_direction = wing_direction.norm();
  wing.setRotation(atan2f(wing_direction.y, wing_direction.x) * 180.0f / 3.1415926535f);
  wing.setScale(1, wing_direction.x > 0 ? 1.0f : -1.0f);
}

void Bird4::soar(float dt) {
  Vector2f wing_normal = wing_direction.i();

  Vector2f wind = air_current - velocity;
  Vector2f r_wind = wind * wing_direction.conj();
  Vector2f P = wing_direction * para_resistance * r_wind.x;
  Vector2f Q = wing_normal * perp_resistance * r_wind.y;
  Vector2f L = wing_normal * -1.0f * lift_coefficient * para_resistance * atanf(r_wind.y / r_wind.x) * sqrtf(M::lengthSQ(wind));
  Vector2f G = {0, gravity};

  if (r_wind.x < 0) {
    velocity += (P + Q + L + G) * dt;
  }
  else {
    Vector2f W = wind * (perp_resistance + para_resistance);
    velocity += (W + G) * dt;
  }
  sprite.setRotation(atan2f(velocity.y, velocity.x) * 180.0f / 3.1415926535f);
  sprite.setScale(1, velocity.x > 0 ? 1.0f : -1.0f);
}

void Bird4::considerFlap() {
  if (spray == 0 && flap_cooldown == 0.0f && stamina >= 1.0f) {
    flap();
  }
}

void Bird4::cooldowns(float dt) {
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

void Bird4::flap() {
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

AbstractLevelElement* Bird4::makeCopy(const Vector2f& spawn_) const {
  return new Bird4(spawn_);
}

AbstractLevelElement* Bird4::makeCopy() const {
  return new Bird4(spawn_location);
}
