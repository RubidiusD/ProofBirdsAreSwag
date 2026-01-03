#include "AbstractPlayer.h"
#include "../../managers/Settings.h"

bool AbstractPlayer::SurfaceCollide(const Surface& surface) {
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

}

void AbstractPlayer::render() {
  S::Window.draw(sprite);
}
