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
  float acceleration_speed = 120.0f;
  float air_acceleration_speed = 30.0f;
  Edge* floor = nullptr;
public:
  float radius = 32.0f;

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
