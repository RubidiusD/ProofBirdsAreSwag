#ifndef BIRDSARESWAG_SURFACE_H
#define BIRDSARESWAG_SURFACE_H

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include <cmath>

struct Collision {
  sf::Vector2f point;
  sf::Vector2f normal;
  Collision(const sf::Vector2f& p, const sf::Vector2f& n) {
    point = p;
    normal = n;
  }
};

// vertices are drawn CLOCKWISE around an object
// so that means COUNTERCLOCKWISE around an interior space
// the normal of a surface is i* the vector
class Surface {
private:
  std::vector<sf::Vector2f> vertices;
public:
  std::shared_ptr<Collision> CollideCircle(const sf::Vector2f& center, float radius) const;
};

#endif // BIRDSARESWAG_SURFACE_H
