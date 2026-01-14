#ifndef BIRDSARESWAG_PARTICLE_H
#define BIRDSARESWAG_PARTICLE_H

#include "AbstractLevelElement.h"

class Particle : public AbstractLevelElement {
protected:
  float duration;
public:
  Particle(const sf::Vector2f& pos, const sf::Vector2f& vel, float dur);
  void update(float dt) override;
};

#endif // BIRDSARESWAG_PARTICLE_H
