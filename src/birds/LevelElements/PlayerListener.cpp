#include "PlayerListener.h"

void PlayerListener::QuarryIs(const Vector2f& pos, float dt) {
  QuarryIsNot(dt);
  state = Chasing;

  if (s.size() == m) {
    for (int index = 0; index != m - 1; index ++) {
      s[index] = s[index + 1];
    }
    s.back().p = pos;
    s.back().t = 0.0f;
  }
  else {
    s.emplace_back(pos);
  }

  c.clear();
  for (int index = 0; index != s.size(); index ++) {
    c.emplace_back();
  }

  switch (s.size()) {
  case (0):
    break;
  case (1):
    c[0] = s[0].p;
    break;
  case (2):
    c[0] = s[0].p - s[0].p * s[0].t + s[1].p * s[0].t;
    c[1] = s[0].p - s[1].p;
    break;
  case (3):
    c[2] = ((s[0].p - s[2].p)(s[0].t - s[1].t) - (s[1].p - s[0].p)(s[2].t - s[0].t)) /
           ((s[1].t - s[2].t) * (s[2].t - s[0].t) * (s[0].t - s[1].t));
    c[1] = (s[0].p - s[1].p) / (s[0].t - s[1].t) - c[2] * (s[0].t + s[1].t);
    c[0] = s[0].p - c[1] * s[0].t - c[2] * s[0].t * s[0].t;
    break;
  case (4):
//    printf("Quality max: ");
    Vector2f a = (s[0].p-s[1].p)/(s[0].t-s[1].t);
    Vector2f b = (a - (s[0].p-s[2].p)/(s[0].t-s[2].t)) / (s[1].t - s[2].t);
    c[3] = (b - (a - (s[0].p-s[3].p)/(s[0].t-s[3].t)) / (s[1].t - s[3].t)) / (s[2].t - s[3].t);
    c[2] = b - c[3]*(s[0].t + s[1].t + s[2].t);
    c[1] = a - c[2]*(s[0].t + s[1].t) - c[3]*(s[0].t*s[0].t + s[0].t*s[1].t + s[1].t*s[1].t);
    c[0] = s[0].p - c[1]*(s[0].t) - c[2]*(s[0].t*s[0].t) - c[3]*(s[0].t*s[0].t*s[0].t);
    break;
  }

//  for (const Vector2f& v : c) {
//    v.print();
//  }
//  printf("\n");
}

void PlayerListener::QuarryIsNot(float dt) {
  state = Idle;
  for (Sighting& sighting : s) {
    sighting.t -= dt;
    state = Guessing;
  }
}

Vector2f PlayerListener::f(float t) {
  float time = 1;
  Vector2f total;
  for (Vector2f& coefficient : c) {
    total += coefficient * time;
    time *= t;
  }
//  printf("F(%f) = ", t);
//  total.print();
//  printf("\n");
  return total;
}

void PlayerListener::setCoefficients(const Vector2f*& coefficients, int number) {
  c.clear();
  for (int index = 0; index != number; index ++) {
    c.emplace_back(coefficients[index]);
  }
}

void PlayerListener::setCoefficient(int index, const Vector2f& value) {
  while (c.size() <= index) {
    c.emplace_back();
  }
  c[index] = value;
}
