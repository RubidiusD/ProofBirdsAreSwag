#ifndef BIRDSARESWAG_CIRCLE_COLLIDER_H
#define BIRDSARESWAG_CIRCLE_COLLIDER_H

#include "../../Vector2f.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <memory>

struct CircleCollider {
public:
  float r;
  Vector2f c;

  bool isInside(const std::shared_ptr<CircleCollider>& rhs) const {
    return (c.disSqr(rhs->c) <= (r+rhs->r)*(r+rhs->r));
  }

  bool isInside(const sf::FloatRect& rhs) const {
    return (
        rhs.left < c.x + r &&
        rhs.top  < c.y + r &&
        rhs.left + rhs.width  > c.x - r &&
        rhs.top  + rhs.height > c.y - r);
  }
};

#endif // BIRDSARESWAG_CIRCLE_COLLIDER_H
