#ifndef BIRDSARESWAG_ABSTRACTPLAYER_H
#define BIRDSARESWAG_ABSTRACTPLAYER_H

#include "../../abstracts/InputSubscriber.h"
#include "AbstractCircle.h"
#include "../LevelElements/Surface.h"
#include "AbstractWind.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class AbstractPlayer : public AbstractCircle, public InputSubscriber {
private:
  static const float GRAVITY;
  static const float ACCELERATION;
  static const float AIR_ACCELERATION;
  static const float JUMP;
  static const float DRAG;
  static const float ELASTIC;
protected:
  Vector2f intent;
  bool jumping = false;
  int lives, max_lives = 3;
  sf::Sprite lives_sprite;
public:
  void update(float dt) override;
  void initialise() override;

  void Move(const Vector2f& vector) override;

  virtual void renderUI();

  void Jump(bool down);
  bool hurt();
  void respawn();
};

#endif // BIRDSARESWAG_ABSTRACTPLAYER_H
