#ifndef BIRDSARESWAG_PARTICLE_H
#define BIRDSARESWAG_PARTICLE_H

#include "../abstracts/AbstractLevelElement.h"

class Particle : public AbstractLevelElement {
protected:
  float duration;
public:
  Particle(const Vector2f& pos, const Vector2f& vel, float dur);
  void update(float dt) override;
};

#endif // BIRDSARESWAG_PARTICLE_H
