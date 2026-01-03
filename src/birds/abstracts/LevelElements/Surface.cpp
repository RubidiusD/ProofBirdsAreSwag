#include "Surface.h"
std::shared_ptr<Collision> Surface::CollideCircle(const sf::Vector2f& c, float r) const {

  std::shared_ptr<Collision> first;
  sf::Vector2f corner;
  std::shared_ptr<Collision> second;

  for (int index = 0; index != vertices.size(); index ++) {
    const sf::Vector2f& a = vertices[index];
    const sf::Vector2f& b = vertices[(index + 1) % vertices.size()];
    const sf::Vector2f& d = b - a;
    const sf::Vector2f& n = {-d.y,d.x};
    const sf::Vector2f& p = a + ((n.x*a.y - c.y*n.x + c.x*n.y - a.x*n.y) / (d.x*n.y - d.y*n.x)) * b;


    if ((p.x-c.x)*(p.x-c.x) + (p.y-c.y)*(p.y*c.y) < r*r) {
      if (first == nullptr) {
        first = std::make_shared<Collision>(p, n);
      } else {
        corner = a;
        second = std::make_shared<Collision>(p, n);
        break;
      }
    }
  }

  if (first == nullptr) {
    return nullptr;
  }
  else if (second == nullptr) {
    return first;
  }
  else {
    return std::make_shared<Collision>(corner, norm(timesI(second->point - first->point)));
  }
}
