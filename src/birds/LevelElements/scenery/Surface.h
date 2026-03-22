#ifndef BIRDSARESWAG_SURFACE_H
#define BIRDSARESWAG_SURFACE_H

#include "../../../Vector2f.hpp"
#include "../CircleCollider.h"
#include <SFML/Graphics.hpp>
#include <memory>

struct Edge;

struct Collision {
  Vector2f point = {};
  Vector2f normal = {};
  Edge* edge = nullptr;
  bool inRange = false;
  float elas = 0.0f;
  Collision(const Vector2f& p, const Vector2f& n, Edge* e, bool inRange);
  Collision(const Vector2f& p, const Vector2f& n, bool inRange, float e2);
  float elasticity(float e) const;
};

struct Edge {
  Vector2f point;
  Edge* next = nullptr;
  Edge* prev = nullptr;
  Vector2f dire;
  Vector2f direN;
  Vector2f norm;
  sf::Sprite sprite;
  sf::RenderTexture rt;
  sf::Text text1;
  sf::Text text2;
  float elasticity = 0.0f;
  float wind_cooldown = 0.0f;

  explicit Edge(const Vector2f& p);
  Edge(const Edge& edge);
  void setNext(Edge* n);
  float getLength() const;
  std::shared_ptr<Collision> CollideCircle(const std::shared_ptr<CircleCollider>& c);
  bool CollidePath(const Vector2f& n, const Vector2f& p) const;
  Vector2f chop(float r) const;
};

// vertices are drawn CLOCKWISE around an object
// so that means COUNTERCLOCKWISE around an interior space
// the normal of a surface is i* the vector
class Surface {
private:
  sf::Sprite pen;
public:
  std::shared_ptr<Collision> CollideCircle(const std::shared_ptr<CircleCollider>& c);
  bool CollidePath(const Vector2f& next, const Vector2f& prev) const;
  void render();
  void initialiseTextures(float particle_rate);

  std::vector<Edge> edges;
  bool active = true;
  bool default_active = true;

  explicit Surface(const std::vector<Vector2f>& points);
  explicit Surface(const std::vector<Vector2f>& points, bool base_active);
};

#endif // BIRDSARESWAG_SURFACE_H
