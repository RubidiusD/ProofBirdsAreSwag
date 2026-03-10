#ifndef BIRDSARESWAG_BIRD2_H
#define BIRDSARESWAG_BIRD2_H

#include "../AbstractCircle.h"
#include "../util/PlayerListener.h"

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
  bool collidesPlayer() const override;

  void initialise() override;
  void update(float dt) override;
  bool isAimGood(const Vector2f& v);
  void remove() override;
  AbstractLevelElement *makeCopy(const Vector2f &spawn_) const override;
  AbstractLevelElement *makeCopy() const override;
  void applyWind(const std::vector<std::shared_ptr<AbstractWind>>& winds) override;
};

#endif // BIRDSARESWAG_BIRD2_H
