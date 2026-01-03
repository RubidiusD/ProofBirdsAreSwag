#ifndef BIRDSARESWAG_MATH_LIB_H
#define BIRDSARESWAG_MATH_LIB_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace M {
sf::Vector2f norm(const sf::Vector2f& v) {
  float mag = v.x * v.x + v.y * v.y;
  return v / sqrtf(mag);
}
sf::Vector2f timesI(const sf::Vector2f& v) {
  return {-v.y, v.x};
}
}

#endif // BIRDSARESWAG_MATH_LIB_H
