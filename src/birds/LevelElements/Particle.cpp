#include "Particle.h"
#include "../../MathLib.h"
#include "../../managers/AssetManager.h"

void Particle::update(float dt) {
  duration -= dt;
  if (duration <= 0.0f) {
    alive = false;
    return;
  }

  velocity += air_current * dt;
  sprite.move(velocity * dt);
}

Particle::Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, float dur) : AbstractLevelElement() {
  sprite.setTexture(AssetManager::getTexture(101));
  sprite.setTextureRect({0, M::Rand4() * 2, 2, 2});
  sprite.setOrigin(1, 1);
  sprite.setPosition(pos);
  velocity = vel;
  duration = dur;
}
