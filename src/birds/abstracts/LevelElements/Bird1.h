#ifndef BIRDSARESWAG_BIRD1_H
#define BIRDSARESWAG_BIRD1_H

#include "AbstractCircle.h"

class Bird1 : AbstractCircle {
private:
  const float gravity = 2.5f;
  const float speed = 480.0f;
  const float para_resistance = 0.1f;
  const float perp_resistance = 0.65f;
  const float lift_coefficient = 10.0f;
protected:
  sf::Sprite wing;
  sf::Vector2f wing_direction;

  sf::Vector2f target;
  sf::Vector2f target_r;

  void fly(float dt);

public:
  void initialise() override;
  void update(float dt) override;
  void render() override;
  void Point(const std::shared_ptr<AbstractCircle>& t);
  void moveTo(const sf::Vector2f &pos) override;
};

#endif // BIRDSARESWAG_BIRD1_H
