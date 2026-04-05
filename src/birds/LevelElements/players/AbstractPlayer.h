#ifndef BIRDSARESWAG_ABSTRACTPLAYER_H
#define BIRDSARESWAG_ABSTRACTPLAYER_H

#include "../../../abstracts/InputSubscriber.h"
#include "../AbstractCircle.h"
#include "../scenery/AbstractWind.h"
#include "../scenery/Surface.h"
#include "../util/ProgressData.h"
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
  static const float RADIUS;
  static const float COYOTE;
protected:
  Vector2f intent;
  bool jumping = false;
  int max_lives = 3;
  int lives = 3;
  sf::Sprite lives_sprite;
  float i_timer = 0.25f;
  float max_i_timer = 0.25f;
  Chapter& chapter;
public:
  AbstractPlayer(const Vector2f& spawn, Chapter& c) : AbstractCircle(spawn), chapter(c) {}

  void update(float dt) override;
  void initialise() override;

  void Move(const Vector2f& vector) override;

  virtual void renderUI();

  void Jump(bool down);
  bool hurt(const Vector2f& source);
  void spawn() override;

protected:
  void onStick() override;
  void onBounce() override;
};

#endif // BIRDSARESWAG_ABSTRACTPLAYER_H
