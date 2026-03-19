#include "AbstractPlayer.h"
#include "../../../managers/AssetManager.h"

const float AbstractPlayer::GRAVITY = 1200.0f;
const float AbstractPlayer::ACCELERATION = 960.0f;
const float AbstractPlayer::AIR_ACCELERATION = 480.0f;
const float AbstractPlayer::JUMP = 360.0f;
const float AbstractPlayer::DRAG = 1.75f;
const float AbstractPlayer::ELASTIC = 0.5f;
const float AbstractPlayer::RADIUS = 16.0f;

void AbstractPlayer::update(float dt) {
  if (jumping && floor1 != nullptr) { // the moment you jump
    velocity += (floor1->norm + intent * 0.5f) * jump_strength;
    unsetFloor(floor1);
    unsetFloor(floor2);
    jumping = false;
  }
  else {
    if (floor1 != nullptr) { // otherwise
      velocity += intent * acceleration_speed * dt;
    } else {
      velocity += intent * air_acceleration_speed * dt;
    }
    velocity.y += gravity * dt;
    air_current -= velocity;
    velocity += air_current * drag_modifier * dt;
  }

  setPosition(hB->c + velocity * dt);

  if (i_timer != 0.0f) {
    i_timer -= dt;
    if (i_timer < 0.0f) {
      i_timer = 0.0f;
    }
  }

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
  hB->r = RADIUS;

  AssetManager::RegisterTexture("Data/images/Player.png", 99);
  sprite.setTexture(AssetManager::getTexture(99));
  sprite.setOrigin(16, 16);

  AssetManager::RegisterTexture("Data/images/Heart.png", 98);
  AssetManager::makeRepeating(98);
  lives_sprite.setTexture(AssetManager::getTexture(98));
  lives_sprite.setTextureRect(sf::IntRect(0, 0, max_lives * 48, 48));
  lives_sprite.setPosition(16, S::Res.y - 64);
}

bool AbstractPlayer::hurt(const Vector2f& source) {
  velocity += (getPosition() - source).norm() * 360.0f;
  if (i_timer != 0.0f) {
    return false;
  }
  i_timer = max_i_timer;
  lives --;
  lives_sprite.setTextureRect({0, 0, lives * 48, 48});
  return !(alive = (lives > 0));
}

void AbstractPlayer::renderUI() {
  S::Window.draw(lives_sprite);
}

void AbstractPlayer::spawn() {
  lives = max_lives;
  lives_sprite.setTextureRect({0, 0, lives * 48, 48});
  velocity.set(0, 0);
  setPosition(spawn_location);
}
