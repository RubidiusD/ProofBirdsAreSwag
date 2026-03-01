#include "Particle.h"
#include "../../MathLib.h"
#include "../../managers/AssetManager.h"

void Particle::update(float dt) {
  duration -= dt;
  if (duration <= 0.0f) {
    alive = false;
    return;
  }

  velocity += (air_current - velocity) * dt;
  sprite.move(velocity * dt);
}

Particle::Particle(const Vector2f& pos, const Vector2f& vel, float dur) : AbstractLevelElement() {
  sprite.setTexture(AssetManager::getTexture(101));
  sprite.setTextureRect({M::Rand4() * 3, M::Rand8() * 3, 3, 3});
  sprite.setOrigin(1, 2);
  sprite.setPosition(pos);
  sprite.setRotation((float)M::Rand(0, 359));
  velocity = vel;
  duration = dur;
}
