#include "AbstractPlayer.h"
#include "../../managers/AssetManager.h"

const float AbstractPlayer::GRAVITY = 1200.0f;
const float AbstractPlayer::ACCELERATION = 960.0f;
const float AbstractPlayer::AIR_ACCELERATION = 480.0f;
const float AbstractPlayer::JUMP = 360.0f;
const float AbstractPlayer::DRAG = 1.0f;
const float AbstractPlayer::ELASTIC = 0.5f;

void AbstractPlayer::update(float dt) {
  if (jumping && floor != nullptr) { // the moment you jump
    velocity += (floor->norm + intent * 0.5f) * jump_strength;
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
    air_current -= velocity;
    velocity += air_current * drag_modifier * dt;
  }

  sprite.move(velocity * dt);

  stickToFloor();
}

void AbstractPlayer::Move(const Vector2f& vector) {
  intent = vector;
}

void AbstractPlayer::Jump(bool down) {
  jumping = down;
}

void AbstractPlayer::initialise() {
  jump_strength = JUMP;
  gravity = GRAVITY;
  acceleration_speed = ACCELERATION;
  air_acceleration_speed = AIR_ACCELERATION;
  drag_modifier = DRAG;
  elasticity = ELASTIC;

  AssetManager::RegisterTexture("Data/images/Player.png", 99);
  sprite.setTexture(AssetManager::getTexture(99));
  sprite.setOrigin(16, 16);
}
