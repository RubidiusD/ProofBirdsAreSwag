#include "AbstractPlayer.h"
#include "../../Settings.h"
#include "../../managers/AssetManager.h"

bool AbstractPlayer::SurfaceCollide(Surface& surface) {
  std::shared_ptr<Collision> collision = surface.CollideCircle(sprite.getPosition(), radius);
  if (collision != nullptr) {
    setPosition(collision->point + collision->normal * radius);

    return true;
  }
  return false;
}

void AbstractPlayer::setPosition(const sf::Vector2f &pos) {
  sprite.setPosition(pos);
}

void AbstractPlayer::update(float dt) {
  if (jumping && floor != nullptr) { // the moment you jump
    velocity = M::norm(floor->norm * 2.0f + intent);
    floor = nullptr;
  }
  else { // while in the air
    velocity += intent * ((floor == nullptr) ? air_acceleration_speed : acceleration_speed) * dt;
  }
  sprite.move(velocity * speed * dt);

  if (floor != nullptr) {

  }
}

void AbstractPlayer::render() {
  S::Window.draw(sprite);
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
}

sf::Vector2f AbstractPlayer::getPosition() const {
  return sprite.getPosition();
}
