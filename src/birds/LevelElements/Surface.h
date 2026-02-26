#ifndef BIRDSARESWAG_SURFACE_H
#define BIRDSARESWAG_SURFACE_H

#include "../../Vector2f.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

struct Edge;

struct Collision {
  Vector2f point = {};
  Vector2f normal = {};
  Edge* edge = nullptr;
  bool inRange = false;
  Collision(const Vector2f& p, const Vector2f& n, Edge* e, bool inRange);
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
  float elasticity = 0.0f;

  explicit Edge(const Vector2f& p);
  Edge(const Edge& edge);
  void setNext(Edge* n);
  float getLength() const;
  std::shared_ptr<Collision> CollideCircle(const Vector2f& c, float r);
  Vector2f chop(float r) const;
};

// vertices are drawn CLOCKWISE around an object
// so that means COUNTERCLOCKWISE around an interior space
// the normal of a surface is i* the vector
class Surface {
private:
  std::vector<Edge> edges;
  sf::Sprite pen;
public:
  std::shared_ptr<Collision> CollideCircle(const Vector2f& center, float radius);
  void render();
  void initialiseTextures();

  explicit Surface(const std::vector<Vector2f>& points);
};

#endif // BIRDSARESWAG_SURFACE_H
