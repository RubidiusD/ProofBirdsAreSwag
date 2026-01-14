#ifndef BIRDSARESWAG_ABSTRACTPLAYER_H
#define BIRDSARESWAG_ABSTRACTPLAYER_H

#include "../../../abstracts/InputSubscriber.h"
#include "AbstractCircle.h"
#include "Surface.h"
#include "Wind.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class AbstractPlayer : public AbstractCircle, public InputSubscriber {
private:
  const float gravity = 2.5f;
  const float speed = 480.0f;
  const float acceleration_speed = 2.0f;
  const float air_acceleration_speed = 1.0f;
protected:
  sf::Vector2f intent;
  bool jumping = false;
public:
  void update(float dt) override;
  void initialise() override;

  void Move(const sf::Vector2f& vector) override;

  void Jump(bool down);
};

#endif // BIRDSARESWAG_ABSTRACTPLAYER_H
