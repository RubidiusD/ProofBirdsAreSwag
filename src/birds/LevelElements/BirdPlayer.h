#ifndef BIRDSARESWAG_BIRD_PLAYER_H
#define BIRDSARESWAG_BIRD_PLAYER_H

#include "../abstracts/AbstractPlayer.h"

class BirdPlayer : public AbstractPlayer {
private:
  const float gravity = 0.75f;
  const float speed = 640.0f;
  const float acceleration_speed = 2.0f;
  const float para_resistance = 0.05f;
  const float perp_resistance = 10.0f;
  const float lift_coefficient = 3.0f;
  const float max_flap = 0.15f;
  const float stamina_refresh = 1.0f;
  const float max_stamina = 10.0f;

protected:
  sf::Sprite wing;
  sf::Vector2f wing_direction;
  float flap_cooldown = 0.0f;
  float stamina = 10.0f;

  void fly(float dt);

public:
  void Look(const sf::Vector2f &vector) override;
  void render() override;
  void update(float dt) override;
  void initialise() override;
  void moveTo(const sf::Vector2f &pos) override;
};

#endif // BIRDSARESWAG_BIRD_PLAYER_H
