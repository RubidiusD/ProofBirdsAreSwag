#ifndef BIRDSARESWAG_ABSTRACT_WIND_H
#define BIRDSARESWAG_ABSTRACT_WIND_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
struct AbstractWind {
  Vector2f velocity;
  sf::Rect<float> bounds;
  bool global;

  AbstractWind(const Vector2f& v, const sf::FloatRect& b) {
    velocity = v;
    bounds = b;
    global = false;
  }

  explicit AbstractWind(const Vector2f& v) {
    velocity = v;
    global = true;
  }

  bool isInside(const Vector2f& center, float radius) const {
    return global || (
        bounds.left < center.x + radius &&
        bounds.top < center.y + radius &&
        bounds.left + bounds.width > center.x - radius &&
        bounds.top + bounds.height > center.y - radius);
  }

  bool isInside(const sf::FloatRect& b) const {
    return global || (
        bounds.left < b.left + b.width &&
        bounds.top < b.top + b.height &&
        bounds.left + bounds.width > b.left &&
        bounds.top + bounds.height > b.top);
  }

  virtual void update(float dt) {}
};

#endif // BIRDSARESWAG_ABSTRACT_WIND_H
