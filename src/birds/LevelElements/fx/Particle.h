#ifndef BIRDSARESWAG_PARTICLE_H
#define BIRDSARESWAG_PARTICLE_H

#include "../AbstractLevelElement.h"

class Particle : public AbstractLevelElement {
protected:
  float duration;
  Vector2f prev_position;
public:
  Particle(const Vector2f& pos, const Vector2f& vel);
  bool surfaceCollide(Surface& surface) override;
  void update(float dt) override;
  bool collidesSurface() const override;
};

#endif // BIRDSARESWAG_PARTICLE_H
