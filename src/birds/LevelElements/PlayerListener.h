#ifndef BIRDSARESWAG_PLAYER_LISTENER_H
#define BIRDSARESWAG_PLAYER_LISTENER_H

#include "../../Vector2f.hpp"
#include "../abstracts/AbstractLevelElement.h"

struct Sighting {
  Vector2f p;
  float t;

  Sighting(const Vector2f& pos, float time) {
    p = pos;
    t = time;
  }
  Sighting(const Vector2f pos) {
    p = pos;
    t = 0.0f;
  }
};

enum ChaseState {
  Idle,
  Chasing,
  Guessing
};

struct PlayerListener {
private:
  std::vector<Sighting> s;
  std::vector<Vector2f> c;
  int m = 4;
  ChaseState state = Idle;

public:
  void QuarryIs(const Vector2f& pos, float dt);
  void QuarryIsNot(float dt);
  Vector2f f(float t);
  Vector2f current_position();
  void setCoefficients(const Vector2f*& coefficients, int number);
  void setCoefficient(int index, const Vector2f& value);
};

#endif // BIRDSARESWAG_PLAYER_LISTENER_H
