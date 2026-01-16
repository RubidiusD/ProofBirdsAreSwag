#ifndef BIRDSARESWAG_MATH_LIB_H
#define BIRDSARESWAG_MATH_LIB_H

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <random>

class M {
public:
  static sf::Vector2f norm(const sf::Vector2f& v);
  static sf::Vector2f timesI(const sf::Vector2f& v);
  static sf::Vector2f scale(const sf::Vector2f& a, const sf::Vector2f& b);
  static sf::Vector2f scale(const sf::Vector2f& a, float b);
  static sf::Vector2f avg(const sf::Vector2f& a, const sf::Vector2f& b);
  static sf::Vector2f times(const sf::Vector2f& a, const sf::Vector2f& b);
  static sf::Vector2f divide(const sf::Vector2f& a, const sf::Vector2f& b);
  static sf::Vector2f cross(const sf::Vector2f& a, const sf::Vector2f& b);
  static bool limit(sf::Vector2f& v);
  static sf::Vector2f conjugate(const sf::Vector2f& v);
  static sf::Vector2f splat(const sf::Vector2f& v, const sf::Vector2f& n);
  static float dot(const sf::Vector2f& a, const sf::Vector2f& b);
  static float distanceSQ(const sf::Vector2f& a, const sf::Vector2f& b);
  static float lengthSQ(const sf::Vector2f& v);
  static float parallelMag(const sf::Vector2f& v, const sf::Vector2f& n);
  static float parallelMag(const sf::Vector2f& v, const sf::Vector2f& n, bool normalised);

  static unsigned MaxU(unsigned a, unsigned b);
  static unsigned MinU(unsigned a, unsigned b);

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