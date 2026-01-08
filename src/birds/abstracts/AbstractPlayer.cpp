#include "AbstractPlayer.h"
#include "../../Settings.h"
#include "../../managers/AssetManager.h"

bool AbstractPlayer::SurfaceCollide(Surface& surface) {
  std::shared_ptr<Collision> collision = surface.CollideCircle(sprite.getPosition(), radius);
  if (collision != nullptr) {
    snapTo(collision);

    return true;
  }
  return false;
}

void AbstractPlayer::setPosition(const sf::Vector2f &pos) {
  sprite.setPosition(pos);
}

void AbstractPlayer::update(float dt) {
  if (jumping && floor != nullptr) { // the moment you jump
    velocity = M::norm(floor->norm * 2.0f + intent + velocity);
    floor = nullptr;
    jumping = false;
  }
  else if (floor != nullptr) { // otherwise
    velocity += intent * acceleration_speed * dt;
  } else {
    velocity.x += intent.x * air_acceleration_speed * dt;
    velocity.y += air_acceleration_speed * dt;
  }
  M::limit(velocity);

  sprite.move(velocity * speed * dt);

  if (floor != nullptr) {
    std::shared_ptr<Collision> cA = floor->prev->CollideCircle(sprite.getPosition(), radius);
    std::shared_ptr<Collision> cB = floor->CollideCircle(sprite.getPosition(), radius);
    std::shared_ptr<Collision> cC = floor->next->CollideCircle(sprite.getPosition(), radius);

    if (cB == nullptr) { // no longer touching current floor
      if (!snapTo(cA) && !snapTo(cC)) {
        floor = nullptr;
      }
    }
    else {
      if (!snapTo(cA, cB) && !snapTo(cB, cC)) {
        snapTo(cB);
      }
    }
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
  sprite.setOrigin(16, 16);
}

sf::Vector2f AbstractPlayer::getPosition() const {
  return sprite.getPosition();
}

bool AbstractPlayer::snapTo(const std::shared_ptr<Collision>& collision) {
  if (collision == nullptr) {
    return false;
  }
  if (collision->edge->norm.y < max_steepness) {
    floor = collision->edge;
  }
  velocity = M::splat(velocity, collision->normal);
  setPosition(collision->point + M::scale(collision->normal, radius));
  return true;
}

bool AbstractPlayer::snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2) {
  if (c1 == nullptr || c2 == nullptr) {
    return false;
  }
  Edge *e1 = c1->edge;
  Edge *e2 = c2->edge;
  setPosition(e2->point + M::scale(e2->dire, radius * ((e1->dire.x*(e2->norm.y- e1->norm.y) - e1->dire.y*(e2->norm.x- e1->norm.x)) /(e2->dire.x* e1->dire.y - e2->dire.y* e1->dire.x))) + M::scale(e2->norm, radius));
  if (e1->norm.y < max_steepness) {
    if (e2->norm.y < max_steepness) {
      floor = (M::Rand2()) ? e1 : e2;
    }
    else {
      floor = e1;
    }
  }
  else {
    if (e2->norm.y < max_steepness) {
      floor = e2;
    }
    else {
      floor = nullptr;
    }
  }
  velocity = M::splat(velocity, e1->norm);
  velocity = M::splat(velocity, e2->norm);
  return true;
}
