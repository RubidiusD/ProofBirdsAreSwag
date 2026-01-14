#ifndef BIRDSARESWAG_ABSTRACT_CIRCLE_H
#define BIRDSARESWAG_ABSTRACT_CIRCLE_H

#include "AbstractLevelElement.h"
#include "Surface.h"
#include "Wind.h"
#include <SFML/Graphics/Sprite.hpp>
class AbstractCircle : public AbstractLevelElement {
protected:
  const float max_steepness = -0.0f;
  Edge* floor = nullptr;
  Edge* floor2 = nullptr;

  void stickToFloor();
  bool setFloor(Edge*&, Edge*) const;
  void unsetFloor(Edge*&) const;

public:
  float radius = 16.0f;

  bool snapTo(const std::shared_ptr<Collision>& collision);
  bool snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2);
  bool SurfaceCollide(Surface& surface);
  void setPosition(const sf::Vector2f& pos);
  void setPosition(const sf::Vector2f& pos, bool override);
  sf::Vector2f getPosition() const;
  void applyWind(const std::vector<std::shared_ptr<Wind>>& winds) override;
};

#endif // BIRDSARESWAG_ABSTRACT_CIRCLE_H
