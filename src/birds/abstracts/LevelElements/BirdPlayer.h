#ifndef BIRDSARESWAG_BIRD_PLAYER_H
#define BIRDSARESWAG_BIRD_PLAYER_H

#include "AbstractPlayer.h"

class BirdPlayer : public AbstractPlayer {
private:
  const float gravity = 2.5f;
  const float speed = 480.0f;
  const float acceleration_speed = 2.0f;
  const float para_resistance = 0.1f;
  const float perp_resistance = 0.65f;
  const float lift_coefficient = 10.0f;

protected:
  sf::Sprite wing;
  sf::Vector2f wing_direction;

  void fly(float dt);

public:
  void Look(const sf::Vector2f &vector) override;
  void render() override;
  void update(float dt) override;
  void initialise() override;
  void moveTo(const sf::Vector2f &pos) override;
};

#endif // BIRDSARESWAG_BIRD_PLAYER_H
