#include "MathLib.h"
#include <chrono>

bool M::limit(Vector2f& v) {
  float mag = v.x * v.x + v.y * v.y;
  if (mag > 1.0f) {
    v = v / sqrtf(mag);
    return true;
  }
  return false;
}

bool M::limit(Vector2f& v, float m) {
  float mag = v.x * v.x + v.y * v.y;
  if (mag < m * m) {
    return false;
  }

  v = v * m / sqrtf(mag);
  return true;
}

bool M::limit(Vector2f& v, float m, float dt) {
  float mag = v.x * v.x + v.y * v.y;
  if (mag < m * m) {
    return false;
  }

  v = v * (1.0f - 3.0f * dt);
  return true;
}

float M::distanceSQ(const Vector2f& a, const Vector2f& b) {
  return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

std::uniform_int_distribution<uint32_t> M::rand2(0,1);
std::uniform_int_distribution<uint32_t> M::rand4(0,3);
std::uniform_int_distribution<uint32_t> M::rand8(0,7);
std::uniform_int_distribution<uint32_t> M::rand;
M::MyRNG M::rng(_abs64(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));

bool M::Rand2() {
  return rand2(rng);
}

unsigned short M::Rand4() {
  return rand4(rng);
}

unsigned short M::Rand8() {
  return rand8(rng);
}

unsigned M::Rand() {
  return rand(rng);
}

unsigned M::Rand(unsigned min, unsigned max) {
  return min + (Rand() % (max - min + 1));
}

float M::Randf(float lower_bound, float upper_bound) {
  return lower_bound + ((float) (Rand() % ((unsigned)(ceilf(upper_bound * 100.0f) - floorf(lower_bound * 100.0f))))) / 100.0f;
}

template <typename T> T M::Min(T a, T b) {
  return (a < b) ? a : b;
}

template <typename T> T M::Max(T a, T b) {
  return (a < b) ? b : a;
}

Vector2f M::splat(const Vector2f& v, const Vector2f& n) {
  Vector2f v2 = {fmaxf(0.0f, v.x*n.x + v.y*n.y), v.y*n.x - v.x*n.y};
  return {v2.x*n.x - v2.y*n.y, v2.y*n.x + v2.x*n.y};
}

float M::lengthSQ(const Vector2f& v) {
  return v.x*v.x + v.y*v.y;
}

float M::parallelMag(const Vector2f& v, const Vector2f& n) {
  return (v.x*n.x + v.y*n.y) / sqrtf(lengthSQ(n));

}

float M::parallelMag(const Vector2f& v, const Vector2f& n, bool normalised) {
  return normalised ? v.x*n.x + v.y*n.y : parallelMag(v, n);
}

Vector2f M::cross(const Vector2f& a, const Vector2f& b) {
  return {a.x * b.x + a.y * b.y, a.y * b.x - a.x + b.y};
}

unsigned M::max(unsigned int a, unsigned int b) {
  return a > b ? a : b;
}
