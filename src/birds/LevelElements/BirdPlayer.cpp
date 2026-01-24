#include "BirdPlayer.h"
#include "../../managers/AssetManager.h"
#include "../levels/LevelLibrary.h"
#include "Particle.h"

void BirdPlayer::initialise() {
  AssetManager::RegisterTexture("Data/images/Bird1.png", 111);
  AssetManager::RegisterTexture("Data/images/Bird1W.png", 112);

  sprite.setTexture(AssetManager::getTexture(111));
  wing.setTexture(AssetManager::getTexture(112));

  sprite.setOrigin(29, 12);
  wing.setOrigin(23, 5);
}

void BirdPlayer::update(float dt) {
  if (jumping && floor != nullptr) { // the moment you jump
    velocity += floor->norm + intent * 0.5f;
    unsetFloor(floor);
    unsetFloor(floor2);
    flap_cooldown = 0.0f;
    jumping = false;
  }
  else if (jumping && flap_cooldown == 0.0f && stamina >= 1.0f) { // the moment you flap (and can)
    velocity += intent * 0.125f + sf::Vector2f(0.0f, -0.09375f);
    jumping = false;
    flap_cooldown = max_flap;
    stamina -= 1.0f;
    for (unsigned index = 0; index != 8; index ++) {
      LevelLibrary::current_level->addElement(new Particle(getPosition(), M::times({0.0f, 1.0f}, M::norm({1.0f, M::Randf(-2.0f, 2.0f)})) * (100.0f + (float)M::Rand(0, 80)), 0.3f));
    }
  }
  else if (floor != nullptr) { // if on ground and not jumping
    velocity += intent * acceleration_speed * dt;
    velocity.y += gravity * dt;
    velocity += air_current * dt / speed;
  } else { // if in air and not jumping
    fly(dt);
    if (flap_cooldown != 0.0f) {
      flap_cooldown -= dt;
      if (flap_cooldown < 0.0f) {
        flap_cooldown = 0.0f;
      }
    }
  }
  M::limit(velocity);

  sprite.setRotation(atan2f(velocity.y, velocity.x) * 180.0f / 3.1415926535f);
  moveTo(sprite.getPosition() + velocity * speed * dt);

  if (stamina < max_stamina) {
    stamina += dt * stamina_refresh;
    if (stamina > max_stamina) {
      stamina = max_stamina;
    }
  }

  stickToFloor();
}

void BirdPlayer::fly(float dt) {
  sf::Vector2f wing_normal = M::timesI(wing_direction); // wing normal

  sf::Vector2f relative_air_current = air_current / speed - velocity; // relative air current
  sf::Vector2f v1 = M::times(relative_air_current, M::conjugate(wing_direction));
  sf::Vector2f P = wing_direction * para_resistance * v1.x;
  sf::Vector2f Q = wing_normal * perp_resistance * v1.y;
  sf::Vector2f L = sf::Vector2f(-relative_air_current.y, relative_air_current.x) * -1.0f * lift_coefficient * asinf(M::norm(v1).y);
  sf::Vector2f G = {0, gravity};

  if (v1.x < 0) {
    velocity += ((P + Q + L) * flap_cooldown / max_flap + G) * dt;
  }
  else {
    sf::Vector2f W = relative_air_current;
    velocity += (W + G) * dt;
  }
}

void BirdPlayer::Look(const sf::Vector2f &vector) {
  wing_direction = M::norm(vector);
  wing.setRotation(atan2f(vector.y, vector.x) * 180.0f / 3.1415926535f);
}

void BirdPlayer::render() {
  AbstractPlayer::render();
  S::Window.draw(wing);
}

void BirdPlayer::moveTo(const sf::Vector2f &pos) {
  sprite.setPosition(pos);
  wing.setPosition(pos);
}
