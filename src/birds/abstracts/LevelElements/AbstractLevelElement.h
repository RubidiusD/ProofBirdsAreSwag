#ifndef BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H
#define BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H

#include "../../../Settings.h"
#include <SFML/Graphics/Sprite.hpp>

class AbstractLevelElement {
protected:
  sf::Sprite sprite;
  sf::Vector2f velocity;

public:
  virtual void update(float dt) { sprite.move(velocity * dt); }
  virtual void render() { S::Window.draw(sprite); }
  virtual void initialise() {}
  virtual void moveTo(const sf::Vector2f& pos) {sprite.setPosition(pos);}
};

#endif // BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H
