#include "BirdPlayer.h"
#include "../../managers/AssetManager.h"

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
  const sf::Vector2f& n = wing_direction;
  sf::Vector2f j = M::timesI(n); // wing normal

  sf::Vector2f v = air_current / speed - velocity; // relative air current
  sf::Vector2f v1 = M::times(v, M::conjugate(n));
  sf::Vector2f P = n * para_resistance * v1.x;
  sf::Vector2f Q = j * perp_resistance * v1.y;
  sf::Vector2f L = j * lift_coefficient * asinf(v1.y) * sqrtf(M::lengthSQ(v));
  sf::Vector2f G = {0, gravity};

  if (v1.x < 0) {
    velocity += (P + Q + L + G) * dt;
  }
  else {
    sf::Vector2f W = v * (perp_resistance + para_resistance);
    velocity += (W + G) * dt;
  }
//  printf("Wing: %f, %f ", wing_direction.x, wing_direction.y);
//  printf("AoA: %f ", atanf(v1.y / v1.x));
//  printf("Lift: %f, %f ", L.x, L.y);
//  printf("Velocity: %f, %f \n", velocity.x, velocity.y);
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
