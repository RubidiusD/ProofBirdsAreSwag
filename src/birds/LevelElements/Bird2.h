#ifndef BIRDSARESWAG_BIRD2_H
#define BIRDSARESWAG_BIRD2_H

#include "../abstracts/AbstractCircle.h"
#include "PlayerListener.h"

class Bird2 : public AbstractCircle, public PlayerListener {
private:
  static const float ELASTIC;
protected:
  sf::Sprite predictions[10];
  PlayerListener eggPredictor;
  float egg_cooldown = 0.0f;
  float egg_max_cooldown = 1.0f;
public:
  void render() override;
  void initialise() override;
  void update(float dt) override;
  bool isAimGood();
};

#endif // BIRDSARESWAG_BIRD2_H
