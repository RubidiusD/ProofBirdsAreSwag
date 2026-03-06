#ifndef BIRDSARESWAG_EGG_H
#define BIRDSARESWAG_EGG_H

#include "../abstracts/AbstractCircle.h"

class Egg : public AbstractCircle {
public:
  Egg(const Vector2f& pos, const Vector2f& vel);
  void initialise() override;
  void update(float dt) override;
  void remove() override;
  void spawn() override;
  bool collidesPlayer() const override;
  void onHitSurface(const std::shared_ptr<Collision>& collision) override;
  void onHitPlayer() override;

private:

};

#endif // BIRDSARESWAG_EGG_H
