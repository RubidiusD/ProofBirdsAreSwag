#include "Bird1.h"
#include "../../../managers/AssetManager.h"

void Bird1::initialise() {
  AssetManager::RegisterTexture("Data/images/Bird1.png", 111);
  AssetManager::RegisterTexture("Data/images/Bird1W.png", 112);

  sprite.setTexture(AssetManager::getTexture(111));
  wing.setTexture(AssetManager::getTexture(112));

  sprite.setOrigin(29, 12);
  wing.setOrigin(23, 5);
}



void Bird1::update(float dt) {
  if (floor == nullptr) {
    fly(dt);
  }
}

void Bird1::fly(float dt) {
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
  sprite.setRotation(atan2f(velocity.y, velocity.x));
}

const float Bird1::speed = 32.0f;
const float Bird1::para_resistance = 0.1f;
const float Bird1::perp_resistance = 0.65f;
const float Bird1::lift_coefficient = 10.0f;

void Bird1::render() {
  AbstractCircle::render();
}

void Bird1::Point(const std::shared_ptr<AbstractCircle> &t) {
  target = t->getPosition();
  target_r = M::norm(target - getPosition());
}

void Bird1::moveTo(const sf::Vector2f &pos) {
  sprite.setPosition(pos);
  wing.setPosition(pos);
}
