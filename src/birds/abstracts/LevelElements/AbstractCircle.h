#ifndef BIRDSARESWAG_ABSTRACT_CIRCLE_H
#define BIRDSARESWAG_ABSTRACT_CIRCLE_H

#include "AbstractLevelElement.h"
#include "Surface.h"
#include "Wind.h"
#include <SFML/Graphics/Sprite.hpp>
class AbstractCircle : public AbstractLevelElement {
protected:
  sf::Vector2f air_current;
  const static float gravity;
  const static float max_steepness;
  Edge* floor = nullptr;
  Edge* floor2 = nullptr;

  void stickToFloor();
  static bool setFloor(Edge*&, Edge*);
  static void unsetFloor(Edge*&);

public:
  float radius = 16.0f;

  bool snapTo(const std::shared_ptr<Collision>& collision);
  bool snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2);
  bool SurfaceCollide(Surface& surface);
  void setPosition(const sf::Vector2f& pos);
  void setPosition(const sf::Vector2f& pos, bool override);
  sf::Vector2f getPosition() const;
  void applyWind(const std::vector<std::shared_ptr<Wind>>& winds);
};

#endif // BIRDSARESWAG_ABSTRACT_CIRCLE_H
