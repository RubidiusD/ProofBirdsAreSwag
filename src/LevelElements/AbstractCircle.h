#ifndef BIRDSARESWAG_ABSTRACT_CIRCLE_H
#define BIRDSARESWAG_ABSTRACT_CIRCLE_H

#include "AbstractLevelElement.h"
#include "CircleCollider.h"
#include "scenery/AbstractWind.h"
#include "scenery/Surface.h"
#include <SFML/Graphics/Sprite.hpp>

class AbstractCircle : public AbstractLevelElement {
protected:
  Edge* floor1 = nullptr;
  bool can_stick = true;

  virtual bool snapTo(const std::shared_ptr<Collision>& collision);
  virtual bool snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2);
  void stickToFloor();
  bool setFloor(Edge*&, Edge*) const;
  void unsetFloor(Edge*&);
  void tickCoyote(float dt);

  float gravity = 640.0f;
  float acceleration_speed = 640.0f;
  float air_acceleration_speed = 640.0f;
  float jump_strength = 640.0f;
  float drag_modifier = 1.0f;
  float elasticity = 0.0f;
  float coyote = 0.0f;
  float max_coyote = 0.0f;
  Vector2f coyote_normal;

  virtual void onStick() {}
  virtual void onBounce() {}
public:
  explicit AbstractCircle(const Vector2f& spawn) : AbstractLevelElement(spawn) {
    hB = std::make_shared<CircleCollider>();
  }
  bool collidesSurface() const override;
  bool surfaceCollide(Surface& surface) override;
  void setPosition(const Vector2f& pos) override;
  void applyWind(const std::vector<std::shared_ptr<AbstractWind>>& winds) override;
  void spawn() override;
  void initialise() override;
  void onHitSurface(const std::shared_ptr<Collision>& collision) override;
  void onHitPlayer() override;
  void bounceOff(const std::shared_ptr<AbstractCircle>& rhs);
};

#endif // BIRDSARESWAG_ABSTRACT_CIRCLE_H
