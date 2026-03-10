#ifndef BIRDSARESWAG_EGGPARTICLE_H
#define BIRDSARESWAG_EGGPARTICLE_H

#include "../../../managers/AssetManager.h"
#include "Particle.h"

class EggParticle : public Particle
{
public:
  EggParticle(const Vector2f& pos, const Vector2f& vel, int index) : Particle(pos, vel) {
    sprite.setTexture(AssetManager::getTexture(102));
    sprite.setTextureRect({0, 6*index, 6, 6});
  }
  void update(float dt) override {
    velocity.y += 640.0f * dt;
    Particle::update(dt);
  }
};

#endif // BIRDSARESWAG_EGGPARTICLE_H
