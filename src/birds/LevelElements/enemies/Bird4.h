#ifndef BIRDSARESWAG_BIRD4_H
#define BIRDSARESWAG_BIRD4_H

#include "AbstractBird.h"

class Bird4 : public AbstractBird {
private:
  static const float ELASTIC;
  static const float GRAVITY;
  static const float ACCELERATION;
  static const float AIR_ACCELERATION;
  static const float RADIUS;

  void cooldowns(float dt);
  void considerFlap();
protected:
  const float flap_max_cooldown = 0.5f;
  const float para_resistance = 0.5f;
  const float perp_resistance = 1.0f;
  const float lift_coefficient = 10.0f;

  void flap();
  void soar(float dt);
  void tiltWing(float dt);
public:
  explicit Bird4(const Vector2f& pos) : AbstractBird(pos) { name = "Pigeon"; }

  void initialise() override;
  void update(float dt) override;
  AbstractLevelElement* makeCopy(const Vector2f &spawn_) const override;
  AbstractLevelElement* makeCopy() const override;
};

#endif // BIRDSARESWAG_BIRD4_H
