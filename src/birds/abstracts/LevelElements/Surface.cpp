#include "Surface.h"
#include "../../../Settings.h"
#include "../../../managers/AssetManager.h"

Surface::Surface(const std::vector<sf::Vector2f>& points) {
  AssetManager::RegisterTexture("Data/images/Pointer.png", 2);
  for (const sf::Vector2f& point : points) {
    edges.emplace_back(point);
  }
  for (unsigned index = 0; index != edges.size() - 1; index ++) {
    edges[index].setNext(&edges[index + 1]);
  }
  edges.back().setNext(&edges[0]);
}

void Surface::initialiseTextures() {
  pen.setTexture(AssetManager::getTexture(100));

  for (Edge& edge : edges) {
    const int length = (int) roundf(edge.getLength() / 4.0f) + 1;
    edge.rt.create(length * 4, 16);
    if (length < 5) {
      const int size1 = (int) M::Rand(1, M::MinU(4, length - 1));
      const int size2 = (int) length - size1;

      pen.setTextureRect({0, (size1 - 1) * 16, 16, 16});
      pen.setPosition(0, 0);
      edge.rt.draw(pen);
      pen.setTextureRect({48, (size2 - 1) * 16, 16, 16});
      pen.setPosition((float)size1 * 4, 0);
      edge.rt.draw(pen);
    }
    else {
      // left
      int position = M::Rand4();
      pen.setPosition((float)position * 4.0f - 12.0f, 0);
      pen.setTextureRect({0, position * 16, 16, 16});
      edge.rt.draw(pen);
      position ++;

      // middle
      while (length - position > 4) {
        pen.setPosition((float)position * 4.0f, 0);
        pen.setTextureRect({(M::Rand2() ? 16 : 32), 16 * M::Rand4(), 16, 16});
        position += 4;
        edge.rt.draw(pen);
      }

      // right
      pen.setPosition((float)position * 4.0f, 0);
      pen.setTextureRect({48, (length - position - 1) * 16, 16, 16});
      edge.rt.draw(pen);
    }
    edge.rt.display();
    edge.sprite.setTexture(edge.rt.getTexture());
    edge.sprite.setOrigin(2.0f * (float) length, 8);
    edge.sprite.setPosition(M::avg(edge.point, edge.next->point) - M::scale(edge.norm, 8));
    edge.sprite.setRotation((atan2f(edge.norm.y, edge.norm.x) * 180.0f / 3.1415926535f)+90);
  }
}

std::shared_ptr<Collision> Surface::CollideCircle(const sf::Vector2f& c, float r) {

  std::shared_ptr<Collision> first = nullptr;
  std::shared_ptr<Collision> second = nullptr;

  for (auto& edge : edges) {
    std::shared_ptr<Collision> collision = edge.CollideCircle(c, r);
    if (collision == nullptr) {
      continue;
    }
    if (first == nullptr) {
      first = collision; continue;
    } else {
      second = collision; break;
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

std::shared_ptr<Collision> Edge::CollideCircle(const sf::Vector2f &c, float r) {
  float t3 = ((norm.x*point.y - c.y*norm.x + c.x*norm.y - point.x*norm.y) / (dire.x*norm.y - dire.y*norm.x));
  if (t3 < 0 || t3 > 1) {
    return nullptr;
  }
  sf::Vector2f p = point + t3 * dire;
  float distance = M::distanceSQ(c, p);
  if (distance > r * r) {
    return nullptr;
  }
  return std::make_shared<Collision>(p, norm, this);
}

Edge::Edge(sf::Vector2f p) { point = p; }

void Edge::setNext(Edge* n) {
  next = n;
  next->prev = this;
  dire = next->point - point;
  norm = M::timesI(M::norm(dire));
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
