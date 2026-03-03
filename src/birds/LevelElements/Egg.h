#ifndef BIRDSARESWAG_EGG_H
#define BIRDSARESWAG_EGG_H

#include "../abstracts/AbstractCircle.h"

class Egg : public AbstractCircle {
public:
  Egg(const Vector2f& pos, const Vector2f& vel);
  void initialise() override;
  void destroy();
  void update(float dt) override;
  bool snapTo(const std::shared_ptr<Collision> &collision) override;
  bool snapTo(const std::shared_ptr<Collision> &c1,
              const std::shared_ptr<Collision> &c2) override;

private:

};

#endif // BIRDSARESWAG_EGG_H
