#ifndef BIRDSARESWAG_BIRD2_H
#define BIRDSARESWAG_BIRD2_H

#include "AbstractBird.h"

class Bird2 : public AbstractBird {
private:
  static const float ELASTIC;
  static const float GRAVITY;
  static const float ACCELERATION;
  static const float AIR_ACCELERATION;
  static const float RADIUS;
  static const float DRAG;

  void cooldowns(float dt);
  void considerFlap();
protected:
  float flap_max_cooldown = 0.5f;

  void flap();
public:
  explicit Bird2(const Vector2f& pos) : AbstractBird(pos) { name = "Bird That Flaps"; }

  void initialise() override;
  void update(float dt) override;
  AbstractLevelElement* makeCopy(const Vector2f &spawn_) const override;
  AbstractLevelElement* makeCopy() const override;
};

#endif // BIRDSARESWAG_BIRD2_H
