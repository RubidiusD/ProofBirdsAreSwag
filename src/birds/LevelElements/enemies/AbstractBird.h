#ifndef BIRDSARESWAG_ABSTRACT_BIRD_H
#define BIRDSARESWAG_ABSTRACT_BIRD_H

#include "../AbstractCircle.h"
#include "../util/PlayerListener.h"

class AbstractBird : public AbstractCircle {
protected:
  PlayerListener playerPredictor;
  PlayerListener eggPredictor;
  PlayerListener selfPredictor;
  float egg_cooldown = 0.0f;
  float egg_max_cooldown = 1.0f;
  float egg_between_cooldown = 0.25f;
  float flap_cooldown = 0.0f;
  int spray = 0;
  int max_spray = 3;

  sf::Sprite wing;
  Vector2f wing_direction = {1.0f, 0.0f};
  float anim_cooldown = 0.125f;
  sf::IntRect wingRect;

  float stamina = 5.0f;
  float max_stamina = 10.0f;

  void tickWing(float dt);
  void considerEgg();
  void setWingRect(const sf::IntRect& rect);

public:
  explicit AbstractBird(const Vector2f& pos) : AbstractCircle(pos) {}
  bool collidesPlayer() const override;
  void initialise() override;
  bool isAimGood(const Vector2f& v);
  void remove() override;

  AbstractLevelElement *makeCopy() const override;
  AbstractLevelElement *makeCopy(const Vector2f &spawn_) const override;
  void setPosition(const Vector2f &pos) override;
  void render() override;
};

#endif // BIRDSARESWAG_ABSTRACT_BIRD_H
