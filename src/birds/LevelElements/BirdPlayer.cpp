#include "BirdPlayer.h"
#include "../../MathLib.h"
#include "../../managers/AssetManager.h"
#include "../levels/LevelLibrary.h"
#include "Particle.h"
#include <cmath>

const float BirdPlayer::GRAVITY = 480.0f;
const float BirdPlayer::JUMP = 128.0f;
const float BirdPlayer::ACCELERATION = 1280.0f;
const float BirdPlayer::AIR_ACCELERATION = 0.0f;

void BirdPlayer::initialise() {
  AssetManager::RegisterTexture("Data/images/Bird1.png", 111);
  AssetManager::RegisterTexture("Data/images/Bird1W.png", 112);

  sprite.setTexture(AssetManager::getTexture(111));
  wing.setTexture(AssetManager::getTexture(112));

  sprite.setOrigin(29, 12);
  wing.setOrigin(23, 5);

  gravity = GRAVITY;
  jump_strength = JUMP;
  acceleration_speed = ACCELERATION;
  air_acceleration_speed = AIR_ACCELERATION;
}

void BirdPlayer::update(float dt) {
  if (jumping && floor != nullptr) { // the moment you jump
    velocity += (floor->norm + intent * 0.5f) * jump_strength;
    unsetFloor(floor);
    unsetFloor(floor2);
    flap_cooldown = 0.0f;
    jumping = false;
  }
  else if (jumping && flap_cooldown == 0.0f && stamina >= 1.0f) { // the moment you flap (and can)
    velocity += (intent + Vector2f(0.0f, -0.75f)) * flap_strength;
    jumping = false;
    flap_cooldown = max_flap;
    stamina -= 1.0f;
    for (unsigned index = 0; index != 8; index ++) {
      LevelLibrary::current_level->addElement(new Particle(getPosition(), Vector2f(1.0f, M::Randf(-2.0f, 2.0f)).norm().i() * (100.0f + (float)M::Rand(0, 80))));
    }
  }
  else if (floor != nullptr) { // if on ground and not jumping
    velocity += intent * acceleration_speed * dt;
    velocity.y += gravity * dt;
    velocity += air_current * dt;

  } else { // if in air and not jumping
    fly(dt);
    if (flap_cooldown != 0.0f) {
      flap_cooldown -= dt;
      if (flap_cooldown < 0.0f) {
        flap_cooldown = 0.0f;
      }
    }
  }

  sprite.setRotation(atan2f(velocity.y, velocity.x) * 180.0f / 3.1415926535f);
  moveTo(velocity * dt + sprite.getPosition());

  if (stamina < max_stamina) {
    stamina += dt * stamina_refresh;
    if (stamina > max_stamina) {
      stamina = max_stamina;
    }
  }

  stickToFloor();
}

void BirdPlayer::fly(float dt) {
  Vector2f wing_normal = wing_direction.i(); // wing normal

  Vector2f relative_air_current = air_current - velocity; // relative air current
  Vector2f v1 = relative_air_current * wing_direction.conj();
  Vector2f P = wing_direction * para_resistance * v1.x;
  Vector2f Q = wing_normal * perp_resistance * v1.y;
  Vector2f L = Vector2f(-relative_air_current.y, relative_air_current.x) * -1.0f * lift_coefficient * asinf(v1.y / v1.mag());
  Vector2f G = {0, gravity};

  if (v1.x < 0) {
    velocity += ((P + Q + L) * flap_cooldown / max_flap + G) * dt;
  }
  else {
    Vector2f W = relative_air_current * drag_modifier;
    velocity += (W + G) * dt;
  }
}

void BirdPlayer::Look(const Vector2f &vector) {
  wing_direction = vector.norm();
  wing.setRotation(atan2f(vector.y, vector.x) * 180.0f / 3.1415926535f);
}

void BirdPlayer::render() {
  AbstractPlayer::render();
  S::Window.draw(wing);
}

void BirdPlayer::moveTo(const Vector2f &pos) {
  sprite.setPosition(pos);
  wing.setPosition(pos);
}
