#include "MathLib.h"
#include <chrono>

sf::Vector2f M::norm(const sf::Vector2f& v) {
  float mag = v.x * v.x + v.y * v.y;
  return v / sqrtf(mag);
}

sf::Vector2f M::timesI(const sf::Vector2f& v) {
  return {-v.y, v.x};
}

sf::Vector2f M::scale(const sf::Vector2f& a, const sf::Vector2f& b) {
  return {a.x * b.x, a.y * b.y};
}

sf::Vector2f M::scale(const sf::Vector2f& a, float b) {
  return {a.x * b, a.y * b};
}

sf::Vector2f M::avg(const sf::Vector2f& a, const sf::Vector2f& b) {
  return {(a.x + b.x) / 2, (a.y + b.y) / 2};
}

sf::Vector2f M::limit(const sf::Vector2f& v) {
  float mag = v.x * v.x + v.y * v.y;
  if (mag > 1) {
    return v / sqrtf(mag);
  }
  return v;
}

float M::distanceSQ(const sf::Vector2f& a, const sf::Vector2f& b) {
  return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

std::uniform_int_distribution<uint32_t> M::rand2(0,1);
std::uniform_int_distribution<uint32_t> M::rand4(0,3);
std::uniform_int_distribution<uint32_t> M::rand;
M::MyRNG M::rng(_abs64(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));

bool M::Rand2() {
  return rand2(rng);
}

unsigned short M::Rand4() {
  return rand4(rng);
}

unsigned M::Rand() {
  return rand(rng);
}

unsigned M::Rand(unsigned int min, unsigned int max) {
  return min + (Rand() % (max - min));
}

unsigned M::MaxU(unsigned int a, unsigned int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

unsigned M::MinU(unsigned int a, unsigned int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}

sf::Vector2f M::splat(const sf::Vector2f& v, const sf::Vector2f& n) {
  sf::Vector2f v2 = {fmaxf(0.0f, v.x*n.x + v.y*n.y), v.y*n.x - v.x*n.y};
  return {v2.x*n.x - v2.y*n.y, v2.y*n.x + v2.x*n.y};
}

float M::dot(const sf::Vector2f& a, const sf::Vector2f& b) {
  return a.x*b.x + a.y*b.y;
}

float M::lengthSQ(const sf::Vector2f& v) {
  return v.x*v.x + v.y*v.y;
}

float M::parallelMag(const sf::Vector2f& v, const sf::Vector2f& n) {
  return (v.x*n.x + v.y*n.y) / sqrtf(lengthSQ(n));

}

float M::parallelMag(const sf::Vector2f& v, const sf::Vector2f& n, bool normalised) {
  return normalised ? v.x*n.x + v.y*n.y : parallelMag(v, n);
}

sf::Vector2f M::times(const sf::Vector2f &a, const sf::Vector2f &b) {
  return {a.x * b.x - a.y * b.y, a.y * b.x + a.x + b.y};
}

sf::Vector2f M::divide(const sf::Vector2f &a, const sf::Vector2f &b) {
  return sf::Vector2f(a.x * b.x + a.y * b.y, a.y * b.x - a.x + b.y) / lengthSQ(b);
}

sf::Vector2f M::conjugate(const sf::Vector2f &v) {
  return {v.x, -v.y};
}
