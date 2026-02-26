#include "Surface.h"
#include "../../MathLib.h"
#include "../../Settings.h"
#include "../../managers/AssetManager.h"

Surface::Surface(const std::vector<Vector2f>& points) {
  AssetManager::RegisterTexture("Data/images/Pointer.png", 2);
  for (const Vector2f& point : points) {
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
    bool right_convex = (M::cross(edge.prev->dire, edge.dire).y >= 0.0f);
    bool left_convex =  (M::cross(edge.dire, edge.next->dire).y >= 0.0f);

    const int length = (int) floorf(edge.getLength() / 4.0f) + (left_convex ? 0 : 2) + (right_convex ? 0 : 2);
    edge.rt.create(length * 4, 16);
    if (length < 5) {
      const int size1 = (int) M::Rand(1, std::min(4, length - 1));
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
    edge.sprite.setPosition(edge.point.avg(edge.next->point) - edge.norm * 8.0f);
    edge.sprite.setRotation((atan2f(edge.norm.y, edge.norm.x) * 180.0f / 3.1415926535f)+90);

    if (left_convex && !right_convex) {
      edge.sprite.move(edge.direN * 4.0f);
    }
    else if (right_convex && !left_convex) {
      edge.sprite.move(edge.direN * -4.0f);
    }
  }
}

std::shared_ptr<Collision> Surface::CollideCircle(const Vector2f& c, float r) {

  std::shared_ptr<Collision> first = nullptr;
  std::shared_ptr<Collision> second = nullptr;

  for (auto& edge : edges) {
    std::shared_ptr<Collision> collision = edge.CollideCircle(c, r);
    if (collision == nullptr || !collision->inRange) {
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
    return std::make_shared<Collision>(second->edge->point, (second->point - first->point).i().norm(), nullptr, true);
  }
}

void Surface::render() {
  for (Edge& edge : edges) {
    S::Window.draw(edge.sprite);
  }
}

std::shared_ptr<Collision> Edge::CollideCircle(const Vector2f& c, float r) {
  float t3 = ((norm.x*point.y - c.y*norm.x + c.x*norm.y - point.x*norm.y) / (dire.x*norm.y - dire.y*norm.x));
  if (t3 < 0 || t3 > 1) {
    return nullptr;
  }
  Vector2f p = point + dire * t3;
  return std::make_shared<Collision>(p, norm, this, M::distanceSQ(c, p) <= r * r);
}

Edge::Edge(const Vector2f& p) { point = p; }

void Edge::setNext(Edge* n) {
  next = n;
  next->prev = this;
  dire = next->point - point;
  direN = dire.norm();
  norm = direN.i();
}

float Edge::getLength() const {
  return sqrtf(M::distanceSQ(point, next->point));
}

Edge::Edge(const Edge& edge) {
  point = edge.point;
}
Vector2f Edge::chop(float r) const {
  return next->point + next->dire * (r * ((dire.x*(next->norm.y - norm.y) - dire.y*(next->norm.x - norm.x)) /(next->dire.x * dire.y - next->dire.y * dire.x))) + next->norm * r;
}

Collision::Collision(const Vector2f& p, const Vector2f& n, Edge* e, bool r) {
  point = p;
  normal = n;
  edge = e;
  inRange = r;
}

float Collision::elasticity(float e) const {
  return fmaxf((edge == nullptr) ? e : (e + edge->elasticity) / 2, 0.0f);
}
