#include "Bird4.h"
#include "../../levels/LevelLibrary.h"

const float Bird4::ELASTIC = -0.25f;
const float Bird4::GRAVITY = 384.0f;
const float Bird4::ACCELERATION = 256.0f;
const float Bird4::AIR_ACCELERATION = 1024.0f;
const float Bird4::RADIUS = 12.0f;
const float Bird4::DRAG = 2.0f;
const float Bird4::JUMP = 256.0f;

void Bird4::initialise() {
  AbstractBird::initialise();

  elasticity = Bird4::ELASTIC;
  gravity = Bird4::GRAVITY;
  acceleration_speed = Bird4::ACCELERATION;
  air_acceleration_speed = Bird4::AIR_ACCELERATION * inv_max_cooldown;
  hB->r = Bird4::RADIUS;
  drag_modifier = Bird4::DRAG; // this is the ground drag modifier lol
  max_stamina = 10.0f;
  jump_strength = Bird4::JUMP;

  can_stick = true;
}

void Bird4::onStick() {
  wing.setTextureRect({0, 0, 29, 27});
  flap_cooldown = 0.0f;
  anim_cooldown = 0.0f;
}

void Bird4::update(float dt) {
  selfPredictor.QuarryIs(getPosition(), dt);
  tiltWing(dt);

  if (floor == nullptr) {
    soar(dt);
    setPosition(hB->c + velocity * dt);
    considerFlap();
    considerEgg();
  }
  else {
    Vector2f intent = playerPredictor.f(0.5f) + Vector2f{0.0f, -100.0f} - selfPredictor.f(0.5f);
    intent.normInPlace();

    if (stamina == max_stamina) { // take off
      velocity += (floor->norm + intent * 0.5f) * jump_strength;
      unsetFloor(floor);
      setWingRect({0, 27, 29, 27});
      flap_cooldown = flap_max_cooldown;
      anim_cooldown = 0.125f;
      last_stroke_down = true;
      LevelLibrary::current_level->spawnParticle(4, hB->c, velocity * -1.0f);
    }
    else {
      velocity += intent * acceleration_speed * dt;
    }
    velocity.y += gravity * dt;
    air_current -= velocity;
    velocity += air_current * drag_modifier * dt;

    setPosition(hB->c + velocity * dt);

    if (floor != nullptr)
      stickToFloor();
  }

  tickWing(dt);
  cooldowns(dt);
}

void Bird4::tickWing(float dt) {
  anim_cooldown -= dt;
  float facing = (wing_direction.x > 0) ? 1 : -1;
  switch (wingRect.top) {
  case (27):
    velocity += wing_direction.rotate(Vector2f{0, -air_acceleration_speed * dt * flap_cooldown});
    break;
  case (54):
    velocity += wing_direction.rotate(Vector2f{0.89508196721f, facing * -0.44590163934f}) * dt * air_acceleration_speed * flap_cooldown;
    break;
  case (81):
    velocity += wing_direction.rotate(Vector2f{0.980198019802f, facing * 0.19801980198f}) * dt * air_acceleration_speed * flap_cooldown;
//    velocity += wing_direction.rotate(Vector2f{0.89508196721f, facing * 0.44590163934f}) * dt * air_acceleration_speed * flap_cooldown;
    break;
  }
  if (anim_cooldown <= 0.0f) {
    anim_cooldown = 0.125f;
    if (wingRect.left == 87) {
      setWingRect({0, 0, 29, 27});
    }
    else {
      wingRect.left += 29;
      setWingRect(wingRect);
    }
  }
}

void Bird4::tiltWing(float dt) {
  if (playerPredictor.getPrecision() < 2) {
    return;
  }
  Vector2f target_direction;
  float disSQ = hB->c.disSqr(playerPredictor.current_position());
  if (floor == nullptr && (selfPredictor.f(0.5f).x > playerPredictor.f(0.5f).x) == (velocity.x > 0.0f)) {
    target_direction = {velocity.x > 0.0f ? 0.1f : -0.1f, -0.9f};
  }
  else if (floor == nullptr && disSQ <= 10000) {
    Vector2f wing_normal = wing_direction.i();
    Vector2f error = playerPredictor.f(1.0f) + Vector2f{0.0f, -100.0f} - selfPredictor.f(1.0f);
    float strength = fminf(error.dot(wing_normal), 100.0f) * 0.001f;
    target_direction = wing_normal * strength * 0.25;
  }
  else {
    target_direction.x = (hB->c.x < playerPredictor.current_position().x) ? 1.0f : -1.0f;
    target_direction.y = -0.2f;
  }

  wing_direction += target_direction * dt;
  wing_direction.normInPlace();

  wing.setRotation(atan2f(wing_direction.y, wing_direction.x) * 180.0f / 3.1415926535f);
  wing.setScale(1, wing_direction.x > 0 ? 1.0f : -1.0f);
}

void Bird4::soar(float dt) {
  Vector2f wing_normal = wing_direction.i();

  Vector2f wind = air_current - velocity;
  Vector2f r_wind = wind.unRotate(wing_direction);
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
  if (spray == 0 && fabsf(wing_direction.y) < 0.3f && (playerPredictor.current_position() - hB->c).norm().dot(wing_direction) >= 0.5f && stamina >= 1.0f) {
    if (flap_cooldown == 0.0f)
      flap();
    else if (flap_cooldown <= flap_max_cooldown / 2) {
      if (last_stroke_down) {
        flapForwards();
      }
      else {
        flapUpwards();
      }
    }
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
  stamina = fminf(stamina + dt * (floor == nullptr ? 0.5f : 1.5f), max_stamina);
}

void Bird4::flapUpwards() {
  Vector2f cur = getPosition();
  Vector2f tar = playerPredictor.current_position();
  Vector2f pre = selfPredictor.f(0.5f);
  Vector2f tarp = playerPredictor.f(0.5f);

  if (cur.y > tar.y - 75.0f && pre.y > tarp.y - 100.0f) {
    setWingRect({0, 27, 29, 27});
    stamina -= 1.0f;
    flap_cooldown = flap_max_cooldown;
    anim_cooldown = 0.125f;
    last_stroke_down = true;
    LevelLibrary::current_level->spawnParticle(4, hB->c, velocity * -1.0f);
  }
}

void Bird4::flapForwards() {
  Vector2f cur = getPosition();
  Vector2f tar = playerPredictor.current_position();
  Vector2f pre = selfPredictor.f(0.5f);
  Vector2f tarp = playerPredictor.f(0.5f);

  if ((cur.x < tar.x - 200.0f && pre.x < tarp.x - 50.0f) || (cur.x > tar.x + 200.0f && pre.x > tarp.x + 50.0f)) {
    setWingRect({0, 81, 29, 27});
    stamina -= 1.0f;
    flap_cooldown = flap_max_cooldown;
    anim_cooldown = 0.125f;
    last_stroke_down = false;
    LevelLibrary::current_level->spawnParticle(4, hB->c, velocity * -1.0f);
  }
}

void Bird4::flap() {
  Vector2f cur = getPosition();
  Vector2f tar = playerPredictor.current_position();
  Vector2f pre = selfPredictor.f(0.5f);
  Vector2f tarp = playerPredictor.f(0.5f);

  if ((cur.x < tar.x - 50.0f && pre.x < tarp.x + 25.0f) || (cur.x > tar.x + 50.0f && pre.x > tarp.x - 25.0f))  { setWingRect({0, 54, 29, 27}); }
  else if (cur.y > tar.y - 75.0f && pre.y > tarp.y - 100.0f) { setWingRect({0, 27, 29, 27}); }
  else { return; }
  stamina -= 1.0f;
  flap_cooldown = flap_max_cooldown;
  anim_cooldown = 0.125f;
  last_stroke_down = true;
  LevelLibrary::current_level->spawnParticle(4, hB->c, velocity * -1.0f);
}

AbstractLevelElement* Bird4::makeCopy(const Vector2f& spawn_) const {
  return new Bird4(spawn_);
}

AbstractLevelElement* Bird4::makeCopy() const {
  return new Bird4(spawn_location);
}
