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
    Vector2f a = (s[0].p-s[1].p)/(s[0].t-s[1].t);
    Vector2f b = (a - (s[0].p-s[2].p)/(s[0].t-s[2].t)) / (s[1].t - s[2].t);
    c[3] = (b - (a - (s[0].p-s[3].p)/(s[0].t-s[3].t)) / (s[1].t - s[3].t)) / (s[2].t - s[3].t);
    c[2] = b - c[3]*(s[0].t + s[1].t + s[2].t);
    c[1] = a - c[2]*(s[0].t + s[1].t) - c[3]*(s[0].t*s[0].t + s[0].t*s[1].t + s[1].t*s[1].t);
    c[0] = s[0].p - c[1]*(s[0].t) - c[2]*(s[0].t*s[0].t) - c[3]*(s[0].t*s[0].t*s[0].t);
    break;
  }
}

void PlayerListener::QuarryIsNot(float dt) {
  state = Idle;
  for (Sighting& sighting : s) {
    sighting.t -= dt;
    state = Guessing;
  }
}

Vector2f PlayerListener::f(float t) const {
  float time = 1;
  Vector2f total;
  for (const Vector2f& coefficient : c) {
    total += coefficient * time;
    time *= t;
  }
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

Vector2f PlayerListener::current_position() const {
  if (!s.empty() || s.back().t == 0.0f) {
    return s.back().p;
  }
  else if (s.empty()) {
    return {};
  }
  else {
    return c[0];
  }
}

float PlayerListener::nearest(const PlayerListener& rhs, float step) const {
  float best_distance, second_best_distance = 999999999999999999999999999.0f;
  float best_time, second_best_time = 0.0f;
  for (int index = 1; index != 9; index ++) {
    float time = step * (float)index;
    float dis = f(time).disSqr(rhs.f(time));
    if (dis < best_distance) {
      second_best_distance = best_distance;
      second_best_time = best_time;
      best_distance = dis;
      best_time = time;
    }
    else if (dis < second_best_distance) {
      second_best_distance = dis;
      second_best_time = time;
    }
  }

  if (fabsf(best_time - second_best_time) == step) {
    for (int index = 0; index != 5; index ++) {
//      float checking_time = (lower_time * upper_dis + upper_time * lower_dis) / (upper_dis + lower_dis);
      float checking_time = (best_time + second_best_time) / 2;
      float checking_dis = f(checking_time).disSqr(rhs.f(checking_time));

      if (checking_dis < best_distance) {
        second_best_distance = best_distance;
        second_best_time = best_time;
        best_distance = checking_dis;
        best_time = checking_time;
      }
      else if (checking_dis < second_best_distance) {
        second_best_distance = checking_dis;
        second_best_time = checking_time;
      }
    }
  }

  return best_distance;
}
