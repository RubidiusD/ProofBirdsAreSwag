#ifndef BIRDSARESWAG_ABSTRACT_BOX_H
#define BIRDSARESWAG_ABSTRACT_BOX_H

#include "../AbstractLevelElement.h"

class AbstractBox : public AbstractLevelElement {
protected:
  sf::FloatRect bounds;
public:
  AbstractBox(Vector2f center, Vector2f extent) : AbstractLevelElement(center) {
    bounds.top    = center.y - extent.y / 2;
    bounds.left   = center.x - extent.x / 2;
    bounds.width  = extent.x / 2;
    bounds.height = extent.y / 2;
  }

  explicit AbstractBox(const sf::FloatRect& bounds_) : AbstractLevelElement({bounds_.left + bounds_.width / 2, bounds_.top + bounds_.height / 2}) {
    bounds = bounds_;
  }

  bool collidesPlayer() const override {
    return true;
  }

  bool circleCollide(const std::shared_ptr<CircleCollider> &rhs) const override {
    return rhs->isInside(bounds);
  }

  void onHitPlayer() override = 0;
};

#endif // BIRDSARESWAG_ABSTRACT_BOX_H
