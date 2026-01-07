#include "Surface.h"
#include "../../../Settings.h"
#include "../../../managers/AssetManager.h"

std::shared_ptr<Collision> Surface::CollideCircle(const sf::Vector2f& c, float r) {

  std::shared_ptr<Collision> first;
  std::shared_ptr<Collision> second;

  for (auto& edge : edges) {
    std::shared_ptr<Collision> collision = edge.CollideCircle(c, r);
    if (collision == nullptr) {
      continue;
    }
    if (M::distanceSQ(c, collision->point) < r*r) {
      if (first == nullptr) {
        first = collision;
      } else {
        second = collision;
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
    return std::make_shared<Collision>(second->edge->point, M::norm(M::timesI(second->point - first->point)), nullptr);
  }
}

void Surface::render() {
  for (Edge& edge : edges) {
    S::Window.draw(edge.sprite);
  }
}

void Surface::initialiseTextures() {
  pen.setTexture(AssetManager::getTexture(100));

  for (Edge& edge : edges) {
    const int length = (int) roundf(edge.getLength() / 8.0f);
    edge.rt.create(length * 8, 32);
    if (length < 5) {
      const int size1 = (int) M::Rand(1, M::MinU(4, length - 1));
      const int size2 = (int) length - size1;

      pen.setTextureRect({0, (size1 - 1) * 32, 32, 32});
      pen.setPosition(0, 0);
      edge.rt.draw(pen);
      pen.setTextureRect({96, (size2 - 1) * 32, 32, 32});
      pen.setPosition((float)size1 * 8, 0);
      edge.rt.draw(pen);
    }
    else {
      // left
      int position = M::Rand4();
      pen.setPosition(0, 0);
      pen.setTextureRect({0, position * 32, 32, 32});
      edge.rt.draw(pen);
      position ++;

      // middle
      while (length - position > 4) {
        pen.setPosition((float)position * 8, 0);
        pen.setTextureRect({(M::Rand2() ? 32 : 64), 32 * M::Rand4(), 32, 32});
        position += 4;
        edge.rt.draw(pen);
      }

      // right
      pen.setPosition((float)position * 8, 0);
      pen.setTextureRect({96, (length - position - 1) * 32, 32, 32});
      edge.rt.draw(pen);
    }
    edge.rt.display();
    edge.sprite.setTexture(edge.rt.getTexture());
    edge.sprite.setOrigin(4.0f * (float) length, 16);
    edge.sprite.setPosition(M::avg(edge.point, edge.next->point) - M::scale(edge.norm, 16));
    edge.sprite.setRotation(atan2f(edge.norm.y, edge.norm.y) * 180.0f / 3.1415926535f);
  }
}

Surface::Surface(const std::vector<sf::Vector2f>& points) {
  for (const sf::Vector2f& point : points) {
    edges.emplace_back(point);
  }
  for (unsigned index = 0; index != edges.size() - 1; index ++) {
    edges[index].setNext(&edges[index + 1]);
  }
  edges.back().setNext(&edges[0]);
}

std::shared_ptr<Collision> Edge::CollideCircle(const sf::Vector2f &c, float r) {
  const sf::Vector2f& a = point;
  const sf::Vector2f& b = next->point;
  sf::Vector2f d = b - a;
  sf::Vector2f n = {-d.y,d.x};

  float t3 = ((n.x*a.y - c.y*n.x + c.x*n.y - a.x*n.y) / (d.x*n.y - d.y*n.x));
  if (t3 < 0 || t3 > 1) {
    return nullptr;
  }
  sf::Vector2f p = a + t3 * b;
  return std::make_shared<Collision>(p, n, this);
}

Edge::Edge(sf::Vector2f p) { point = p; }

void Edge::setNext(Edge* n) {
  next = n;
  next->prev = this;
  norm = M::timesI(M::norm(next->point - point));
}

float Edge::getLength() const {
  return sqrtf(M::distanceSQ(point, next->point));
}
Edge::Edge(const Edge& edge) {
  point = edge.point;
  next = edge.next;
  prev = edge.prev;
}

Collision::Collision(const sf::Vector2f &p, const sf::Vector2f &n, Edge *e) {
  point = p;
  normal = n;
  edge = e;
}
