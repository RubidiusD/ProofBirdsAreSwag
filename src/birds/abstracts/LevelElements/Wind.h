#ifndef BIRDSARESWAG_WIND_H
#define BIRDSARESWAG_WIND_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
struct Wind {
  sf::Vector2f velocity;
  sf::Rect<float> bounds;
  bool global;

  Wind(const sf::Vector2f& v, const sf::FloatRect& b) {
    velocity = v;
    bounds = b;
    global = false;
  }

  explicit Wind(const sf::Vector2f& v) {
    velocity = v;
    global = true;
  }

  bool isInside(const sf::Vector2f& center, float radius) const {
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

  void update(float dt) {}
};

#endif // BIRDSARESWAG_WIND_H
