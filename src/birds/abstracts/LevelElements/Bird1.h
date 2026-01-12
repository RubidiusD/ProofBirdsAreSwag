#ifndef BIRDSARESWAG_BIRD1_H
#define BIRDSARESWAG_BIRD1_H

#include "AbstractCircle.h"

class Bird1 : AbstractCircle {
protected:
  const static float speed;
  const static float para_resistance;
  const static float perp_resistance;
  const static float lift_coefficient;

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

private:
  void moveTo(const sf::Vector2f &pos) override;
};

#endif // BIRDSARESWAG_BIRD1_H
