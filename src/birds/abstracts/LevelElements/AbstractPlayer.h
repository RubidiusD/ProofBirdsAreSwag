#ifndef BIRDSARESWAG_ABSTRACTPLAYER_H
#define BIRDSARESWAG_ABSTRACTPLAYER_H

#include "AbstractCircle.h"
#include "Surface.h"
#include "Wind.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class AbstractPlayer : public AbstractCircle {
protected:
  sf::Vector2f intent;
  bool jumping = false;
  const static float speed;
  const static float acceleration_speed;
  const static float air_acceleration_speed;
public:
  void update(float dt) override;
  void initialise() override;
  void Move(const sf::Vector2f& vector);
  void Jump(bool down);
};

#endif // BIRDSARESWAG_ABSTRACTPLAYER_H
