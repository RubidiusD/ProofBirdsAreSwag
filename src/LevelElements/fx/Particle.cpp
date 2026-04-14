#include "Particle.h"
#include "../../MathLib.h"
#include "../../managers/AssetManager.h"

void Particle::update(float dt) {
  prev_position = sprite.getPosition();
  duration -= dt;
  if (duration <= 0.0f) {
    alive = false;
    return;
  }

  velocity += (air_current - velocity) * dt;
  sprite.move(velocity * dt);
}
void Particle::spawn() { alive = false; }

bool Particle::collidesSurface() const {
  return true;
}

Particle::Particle(const Vector2f& pos, const Vector2f& vel) : AbstractLevelElement(pos) {
  sprite.setTexture(AssetManager::getTexture(101));
  sprite.setTextureRect({M::Rand4() * 3, M::Rand8() * 3, 3, 3});
  sprite.setOrigin(1, 2);
  sprite.setPosition(pos);
  sprite.setRotation((float)M::Rand(0, 359));
  velocity = vel;
  duration = 20.0f;
//  destroy_on_load = true;
}

bool Particle::surfaceCollide(Surface& surface) {
  if (surface.CollidePath(sprite.getPosition(), prev_position)) {
    alive = false;
  }
  return !alive;
}
