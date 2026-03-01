#ifndef BIRDSARESWAG_ABSTRACT_WIND_H
#define BIRDSARESWAG_ABSTRACT_WIND_H

#include "../../MathLib.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
struct AbstractWind {
  Vector2f velocity;
  Vector2f base_velocity;
  float variance = 0.0f;
  float variance_timer = 0.0f;
  sf::Rect<float> bounds;
  bool global;

  AbstractWind(const Vector2f& v, const sf::FloatRect& b) {
    velocity = base_velocity = v;
    bounds = b;
    global = false;
  }

  explicit AbstractWind(const Vector2f& v) {
    velocity = base_velocity = v;
    global = true;
  }

  AbstractWind(const Vector2f& v, float v2) {
    velocity = base_velocity = v;
    variance = v2;
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

  virtual void update(float dt) {
    if (variance != 0.0f) {
      variance_timer -= dt;
      if (variance_timer <= 0.0f) {
        variance_timer = variance;
//        velocity = base_velocity.rotate(Vector2f(1, M::Randf(-variance, variance)).norm());
        velocity = velocity.rotate(Vector2f(1, M::Randf(-variance, variance)).norm());

      }
    }
  }
};

#endif // BIRDSARESWAG_ABSTRACT_WIND_H
