#include "BirdPlayer.h"
#include "../../../managers/AssetManager.h"

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
    jumping = false;
  }
  else {
    if (floor != nullptr) { // otherwise
      velocity += intent * acceleration_speed * dt;
      velocity.y += gravity * dt;
      velocity += air_current * dt / speed;
    } else {
      fly(dt);
    }
  }
  M::limit(velocity);

  sprite.setRotation(atan2f(velocity.y, velocity.x) * 180.0f / 3.1415926535f);
  moveTo(sprite.getPosition() + velocity * speed * dt);

  stickToFloor();
}

void BirdPlayer::fly(float dt) {
  sf::Vector2f wing_normal = M::timesI(wing_direction);

  sf::Vector2f wind = air_current / speed - velocity;
  sf::Vector2f r_wind = M::times(wind, M::conjugate(wing_direction));
  sf::Vector2f P = wing_direction * para_resistance * r_wind.x;
  sf::Vector2f Q = wing_normal * perp_resistance * r_wind.y;
  sf::Vector2f L = wing_normal * -1.0f * lift_coefficient * para_resistance * atanf(r_wind.y / r_wind.x) * sqrtf(M::lengthSQ(wind));
  sf::Vector2f G = {0, gravity};

  if (r_wind.x < 0) {
    velocity += (P + Q + L + G) * dt;
  }
  else {
    sf::Vector2f W = wind * (perp_resistance + para_resistance);
    velocity += (W + G) * dt;
  }
}

void BirdPlayer::Look(const sf::Vector2f &vector) {
  wing_direction = vector;
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
