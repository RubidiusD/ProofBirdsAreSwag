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

Surface::Surface(const std::vector<Vector2f>& points, bool base_active) : Surface(points) {
  active = default_active = base_active;
}

void Surface::initialiseTextures(float particle_rate) {
  pen.setTexture(AssetManager::getTexture(100));

  for (Edge& edge : edges) {
    edge.wind_cooldown = M::Randf(0.0f, particle_rate);

    const int length = (int) floorf(edge.getLength() / 4.0f) + (edge.concave ? 2 : 0) + (edge.next->concave ? 2 : 0);
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

    if (!edge.concave && edge.next->concave) {
      edge.sprite.move(edge.direN * 4.0f);
    }
    else if (!edge.next->concave && edge.concave) {
      edge.sprite.move(edge.direN * -4.0f);
    }
  }
}

std::shared_ptr<Collision> Surface::CollideCircle(const std::shared_ptr<CircleCollider>& c) {
  if (!active)
    return nullptr;

  std::shared_ptr<Collision> first = nullptr;
  std::shared_ptr<Collision> second = nullptr;

  for (auto& edge : edges) {
    std::shared_ptr<Collision> collision = edge.CollideCircle(c);
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

bool Surface::CollidePath(const Vector2f& next, const Vector2f& prev) const {
  if (!active)
    return false;
  return std::any_of(edges.cbegin(), edges.cend(), [&](const Edge& edge) { return edge.CollidePath(next, prev); });
}

void Surface::render() {
  if (active) {
    for (Edge& edge : edges) {
      S::Window.draw(edge.sprite);
      S::Window.draw(edge.text1);
      S::Window.draw(edge.text2);
    }
  }
}

std::shared_ptr<Collision> Edge::CollideCircle(const std::shared_ptr<CircleCollider>& c) {
  float t3 = ((norm.x*point.y - c->c.y*norm.x + c->c.x*norm.y - point.x*norm.y) / (dire.x*norm.y - dire.y*norm.x));
  if (t3 < 0 || t3 > 1) {
    return nullptr;
  }
  Vector2f p = point + dire * t3;
  return std::make_shared<Collision>(p, norm, this, c->c.disSqr(p) <= (c->r + 2) * (c->r + 2));
}

bool Edge::CollidePath(const Vector2f& n, const Vector2f& p) const {
  float t2 = ((p.y - point.y) * dire.x - (p.x - point.x) * dire.y) / ((n.x - p.x) * dire.y - (n.y - p.y) * dire.x);
  float t1 = (p.x + t2 * (n.x - p.x) - point.x) / (dire.x);

  return (t2 >= 0.0f && t2 <= 1.0f && t1 >= 0.0f && t1 <= 1.0f);
}

Edge::Edge(const Vector2f& p) {
  point = p;
  text1.setCharacterSize(18);
  text1.setString(p.to_string());
  text1.setPosition(p + Vector2f{0, 10});
  text1.setFillColor(sf::Color::White);
  text1.setFont(AssetManager::getFont(0));
  text2.setCharacterSize(18);
  text2.setString(p.to_string());
  text2.setPosition(p + Vector2f{0.5, 10.5});
  text2.setFillColor(sf::Color::Black);
  text2.setFont(AssetManager::getFont(0));
}

void Edge::setNext(Edge* n) {
  next = n;
  next->prev = this;
  dire = next->point - point;
  direN = dire.norm();
  norm = direN.i();
  next->concave = dire.unRotate(next->dire).y < 0.0f;
}

float Edge::getLength() const {
  return sqrtf(M::distanceSQ(point, next->point));
}

Edge::Edge(const Edge& edge) : Edge(edge.point) {}

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
  return fmaxf(0.0f, (e + (edge == nullptr ? elas : edge->elasticity)) / 2.0f);
}

Collision::Collision(const Vector2f &p, const Vector2f &n, bool inRange, float e2) : Collision(p, n, nullptr, inRange) {
  elas = e2;
}
