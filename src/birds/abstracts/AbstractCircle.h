#ifndef BIRDSARESWAG_ABSTRACT_CIRCLE_H
#define BIRDSARESWAG_ABSTRACT_CIRCLE_H

#include "AbstractLevelElement.h"
#include "../LevelElements/Surface.h"
#include "AbstractWind.h"
#include <SFML/Graphics/Sprite.hpp>

class AbstractCircle : public AbstractLevelElement {
protected:
  const float max_steepness = -0.0f;
  Edge* floor = nullptr;
  Edge* floor2 = nullptr;

  void stickToFloor();
  bool setFloor(Edge*&, Edge*) const;
  void unsetFloor(Edge*&) const;

  float gravity = 640.0f;
  float acceleration_speed = 640.0f;
  float air_acceleration_speed = 640.0f;
  float jump_strength = 640.0f;
  float drag_modifier = 1.0f;
  float elasticity = 0.0f;

public:
  AbstractCircle(const Vector2f& spawn) : AbstractLevelElement(spawn) {}

  float radius = 16.0f;

  virtual bool snapTo(const std::shared_ptr<Collision>& collision);
  virtual bool snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2);
  bool surfaceCollide(Surface& surface) override;
  void setPosition(const Vector2f& pos) override;
  void setPosition(const Vector2f& pos, bool override) override;
  bool circleCollide(const Vector2f& c, float r) const override;
  void applyWind(const std::vector<std::shared_ptr<AbstractWind>>& winds) override;
  void spawn() override;
};

#endif // BIRDSARESWAG_ABSTRACT_CIRCLE_H
