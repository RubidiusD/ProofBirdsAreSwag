#ifndef BIRDSARESWAG_ABSTRACTPLAYER_H
#define BIRDSARESWAG_ABSTRACTPLAYER_H

#include "LevelElements/Surface.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class AbstractPlayer {
protected:
  sf::Sprite sprite;
public:
  float radius = 32.0f;

  bool SurfaceCollide(const Surface& surface);
  void setPosition(const sf::Vector2f& pos);
  void update(float dt);
  void render();
};

#endif // BIRDSARESWAG_ABSTRACTPLAYER_H
