#ifndef BIRDSARESWAG_BIRD2_H
#define BIRDSARESWAG_BIRD2_H

#include "../abstracts/AbstractCircle.h"
#include "PlayerListener.h"

class Bird2 : public AbstractCircle {
private:
  static const float ELASTIC;
  static const float GRAVITY;
  static const float ACCELERATION;
  static const float AIR_ACCELERATION;
  static const float JUMP;
  static const float RADIUS;
  static const float DRAG;
protected:
  sf::Sprite predictions[10];
  PlayerListener playerPredictor;
  PlayerListener eggPredictor;
  PlayerListener selfPredictor;
  float egg_cooldown = 0.0f;
  float egg_max_cooldown = 1.0f;
  float egg_between_cooldown = 0.25f;
  int spray = 0;
  int max_spray = 3;
  float flap_cooldown = 0.0f;
  float flap_max_cooldown = 0.25f;

  void flap();
  void cooldowns(float dt);
public:
  Bird2(const Vector2f& pos) : AbstractCircle(pos) {}

  void render() override;
  void initialise() override;
  void update(float dt) override;
  bool isAimGood(const Vector2f& v);
  void remove() override;
};

#endif // BIRDSARESWAG_BIRD2_H
