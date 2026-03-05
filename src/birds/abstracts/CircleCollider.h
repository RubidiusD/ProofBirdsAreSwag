#ifndef BIRDSARESWAG_CIRCLE_COLLIDER_H
#define BIRDSARESWAG_CIRCLE_COLLIDER_H

#include "../../Vector2f.hpp"
#include <memory>

struct CircleCollider {
public:
  float r;
  Vector2f c;

  bool isInside(const std::shared_ptr<CircleCollider>& rhs) const {
    return (c.disSqr(rhs->c) <= (r+rhs->r)*(r+rhs->r));
  }
};

#endif // BIRDSARESWAG_CIRCLE_COLLIDER_H
