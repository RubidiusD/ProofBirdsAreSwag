#ifndef BIRDSARESWAG_BIRD3_H
#define BIRDSARESWAG_BIRD3_H

#include "AbstractBird.h"

class Bird3 : public AbstractBird {
private:
  static const float ELASTIC;
  static const float AIR_ACCELERATION;
  static const float RADIUS;
  static const float DRAG;

  void cooldowns(float dt);
public:
  explicit Bird3(const Vector2f& pos) : AbstractBird(pos) { name = "Bird that Schmoves"; }

  void initialise() override;
  void update(float dt) override;
  AbstractLevelElement* makeCopy(const Vector2f& spawn_) const override;
  AbstractLevelElement* makeCopy() const override;
  void onHitSurface(const std::shared_ptr<Collision>& collision) override;
};

#endif // BIRDSARESWAG_BIRD3_H
