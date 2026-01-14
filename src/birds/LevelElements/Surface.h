#ifndef BIRDSARESWAG_SURFACE_H
#define BIRDSARESWAG_SURFACE_H

#include "../../MathLib.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>
#include <vector>

struct Edge;

struct Collision {
  sf::Vector2f point = {};
  sf::Vector2f normal = {};
  Edge* edge = nullptr;
  bool inRange = false;
  Collision(const sf::Vector2f& p, const sf::Vector2f& n, Edge* e, bool inRange);
};

struct Edge {
  sf::Vector2f point;
  Edge* next = nullptr;
  Edge* prev = nullptr;
  sf::Vector2f dire;
  sf::Vector2f norm;
  sf::Sprite sprite;
  sf::RenderTexture rt;

  explicit Edge(sf::Vector2f p);
  Edge(const Edge& edge);
  void setNext(Edge* n);
  float getLength() const;
  std::shared_ptr<Collision> CollideCircle(const sf::Vector2f& c, float r);
};

// vertices are drawn CLOCKWISE around an object
// so that means COUNTERCLOCKWISE around an interior space
// the normal of a surface is i* the vector
class Surface {
private:
  std::vector<Edge> edges;
  sf::Sprite pen;
public:
  std::shared_ptr<Collision> CollideCircle(const sf::Vector2f& center, float radius);
  void render();
  void initialiseTextures();

  explicit Surface(const std::vector<sf::Vector2f>& points);
};

#endif // BIRDSARESWAG_SURFACE_H
