#ifndef BIRDSARESWAG_VECTOR2F_HPP
#define BIRDSARESWAG_VECTOR2F_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdio>

struct Vector2f {
  float x = 0.0f;
  float y = 0.0f;

  Vector2f() = default;
  Vector2f(const Vector2f& rhs) = default;
  Vector2f(float x_, float y_) { x = x_; y = y_; }
  template<typename T> Vector2f(T x_, T y_) { x = (float)x_; y = (float)y_; }
  Vector2f(const sf::Vector2f& rhs) { x = rhs.x; y = rhs.y; }
  template<typename T> Vector2f(const sf::Vector2<T>& rhs) { x = (float)rhs.x; y = (float)rhs.y; }

  operator sf::Vector2f() const { return {x, y}; }
  template<typename T> operator sf::Vector2<T>() const { return {(T)x, (T)y}; }

  Vector2f& set(float x_, float y_) { x = x_; y = y_; return *this; }
  Vector2f& set(const Vector2f& rhs) { x = rhs.x; y = rhs.y; return *this; }

  Vector2f operator+(const Vector2f& rhs) const { return {x + rhs.x, y + rhs.y}; }
  Vector2f operator-(const Vector2f& rhs) const { return {x - rhs.x, y - rhs.y}; }
  Vector2f operator*(const Vector2f& rhs) const { return {x * rhs.x, y * rhs.y}; }
  Vector2f operator/(const Vector2f& rhs) const { return {x / rhs.x, y / rhs.y}; }
  Vector2f operator+(float rhs) const { return {x + rhs, y + rhs}; }
  Vector2f operator-(float rhs) const { return {x - rhs, y - rhs}; }
  Vector2f operator*(float rhs) const { return {x * rhs, y * rhs}; }
  Vector2f operator/(float rhs) const { return {x / rhs, y / rhs}; }

  Vector2f& operator+=(const Vector2f& rhs) { return set(x + rhs.x, y + rhs.y); }
  Vector2f& operator-=(const Vector2f& rhs) { return set(x - rhs.x, y - rhs.y); }
  Vector2f& operator*=(const Vector2f& rhs) { return set(x * rhs.x, y * rhs.y); }
  Vector2f& operator/=(const Vector2f& rhs) { return set(x / rhs.x, y / rhs.y); }
  Vector2f& operator+=(float rhs) { return set(x + rhs, y + rhs); }
  Vector2f& operator-=(float rhs) { return set(x - rhs, y - rhs); }
  Vector2f& operator*=(float rhs) { return set(x * rhs, y * rhs); }
  Vector2f& operator/=(float rhs) { return set(x / rhs, y / rhs); }

  Vector2f operator()(const Vector2f& rhs) const { return {x * rhs.x, y * rhs.y}; }
  Vector2f operator()(float rhs) const { return {x * rhs, y * rhs}; }
  float operator[](unsigned long long index) const { return (index == 1) ? y : x; }

  Vector2f conj() const { return {x, -y}; }
  Vector2f   rotate(const Vector2f& rhs) const { return {x*rhs.x - y*rhs.y, y*rhs.x + x*rhs.y}; }
  Vector2f unRotate(const Vector2f& rhs) const { return {x*rhs.x + y*rhs.y, y*rhs.x - x*rhs.y}; }
  Vector2f splat(const Vector2f& n, float e) const {
    float x_ = x*n.x + y*n.y;
    Vector2f v2 = {((x_>0) ? x_ : -e*x_), y*n.x - x*n.y};
    return {v2.x*n.x - v2.y*n.y, v2.y*n.x + v2.x*n.y};
  }
  Vector2f cpy() const { return {x, y}; }
  Vector2f norm() const { return cpy() / sqrtf(magSqr()); };
  Vector2f avg(const Vector2f& rhs) const { return (cpy() + rhs) / 2; }
  Vector2f i() const { return {-y, x}; }
  float magSqr() const { return x*x + y*y; }
  float mag() const { return sqrtf(magSqr()); }
  float disSqr(const Vector2f& rhs) const { return (x-rhs.x)*(x-rhs.x) + (y-rhs.y)*(y-rhs.y); }
  float dis(const Vector2f& rhs) const { return sqrtf(disSqr(rhs)); }
  float dot(const Vector2f& rhs) const { return x*rhs.x + y*rhs.y; }
  void print() const { printf("(%f, %f)", x, y); }
};

#endif // BIRDSARESWAG_VECTOR2F_HPP
