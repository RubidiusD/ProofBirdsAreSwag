#include "AbstractPlayer.h"
#include "../../../Settings.h"
#include "../../../managers/AssetManager.h"

void AbstractPlayer::update(float dt) {
  if (jumping && floor != nullptr) { // the moment you jump
    velocity += floor->norm + intent * 0.5f;
    unsetFloor(floor);
    unsetFloor(floor2);
    jumping = false;
  }
  else {
    if (floor != nullptr) { // otherwise
      velocity += intent * acceleration_speed * dt;
    } else {
      velocity += intent * air_acceleration_speed * dt;
    }
    velocity.y += gravity * dt;
    velocity += air_current * dt / speed;
  }
  M::limit(velocity);

  sprite.move(velocity * speed * dt);

  stickToFloor();
}

void AbstractPlayer::Move(const sf::Vector2f& vector) {
  intent = vector;
}

void AbstractPlayer::Jump(bool down) {
  jumping = down;
}

void AbstractPlayer::initialise() {
  AssetManager::RegisterTexture("Data/images/Player.png", 99);
  sprite.setTexture(AssetManager::getTexture(99));
  sprite.setOrigin(16, 16);
}
