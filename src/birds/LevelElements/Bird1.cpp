#include "Bird1.h"
#include "../../MathLib.h"
#include "../../managers/AssetManager.h"
#include <cmath>

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
  sprite.setRotation(atan2f(velocity.y, velocity.x));
}

void Bird1::render() {
  AbstractCircle::render();
  S::Window.draw(wing);
}

void Bird1::Point(const std::shared_ptr<AbstractCircle> &t) {
  target = t->getPosition();
  target_r = (target - getPosition()).norm();
}

void Bird1::moveTo(const Vector2f &pos) {
  sprite.setPosition(pos);
  wing.setPosition(pos);
}
