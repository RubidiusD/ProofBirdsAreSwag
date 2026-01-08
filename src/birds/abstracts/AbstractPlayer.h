#ifndef BIRDSARESWAG_ABSTRACTPLAYER_H
#define BIRDSARESWAG_ABSTRACTPLAYER_H

#include "LevelElements/Surface.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class AbstractPlayer {
protected:
  sf::Sprite sprite;
  sf::Vector2f velocity;
  float speed = 120.0f;
  sf::Vector2f intent;
  bool jumping = false;
  float acceleration_speed = 8.0f;
  float air_acceleration_speed = 2.0f;
public:
  Edge* floor = nullptr;
  float radius = 32.0f;

  bool snapTo(const std::shared_ptr<Collision>& collision);
  bool snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2);
  bool SurfaceCollide(Surface& surface);
  void setPosition(const sf::Vector2f& pos);
  sf::Vector2f getPosition() const;
  void update(float dt);
  void render();
  void Move(const sf::Vector2f& vector);
  void Jump(bool down);
  void initialise();
};

#endif // BIRDSARESWAG_ABSTRACTPLAYER_H
