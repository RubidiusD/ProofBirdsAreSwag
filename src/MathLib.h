#ifndef BIRDSARESWAG_MATH_LIB_H
#define BIRDSARESWAG_MATH_LIB_H

#include "Vector2f.hpp"
#include <random>

class M {
public:
  static Vector2f cross(const Vector2f& a, const Vector2f& b);
  static bool limit(Vector2f& v);
  static bool limit(Vector2f& v, float m);
  static bool limit(Vector2f& v, float m, float dt);
  static Vector2f splat(const Vector2f& v, const Vector2f& n);
  static float distanceSQ(const Vector2f& a, const Vector2f& b);
  static float lengthSQ(const Vector2f& v);
  static float parallelMag(const Vector2f& v, const Vector2f& n);
  static float parallelMag(const Vector2f& v, const Vector2f& n, bool normalised);

  template<typename T> static T Max(T a, T b);
  template<typename T> static T Min(T a, T b);

  static bool Rand2();
  static unsigned short Rand4();
  static unsigned Rand();
  static unsigned Rand(unsigned lower_bound, unsigned upper_bound);
  static float Randf(float lower_bound, float upper_bound);

private:
  typedef std::mt19937 MyRNG;
  static MyRNG rng;
  static std::uniform_int_distribution<uint32_t> rand2;
  static std::uniform_int_distribution<uint32_t> rand4;
  static std::uniform_int_distribution<uint32_t> rand;
};

#endif // BIRDSARESWAG_MATH_LIB_H