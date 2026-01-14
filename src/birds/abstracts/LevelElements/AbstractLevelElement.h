#ifndef BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H
#define BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H

#include "../../../Settings.h"
#include "Wind.h"
#include <SFML/Graphics/Sprite.hpp>

class AbstractLevelElement {
protected:
  sf::Sprite sprite;
  sf::Vector2f velocity;
  sf::Vector2f air_current;

public:
  bool alive = true;

  virtual void update(float dt) { sprite.move(velocity * dt); }
  virtual void render() { S::Window.draw(sprite); }
  virtual void initialise() {}
  virtual void moveTo(const sf::Vector2f& pos) {sprite.setPosition(pos);}
  virtual void applyWind(const std::vector<std::shared_ptr<Wind>>& winds) {
    air_current.x = 0.0f; air_current.y = 0.0f;
    for (const std::shared_ptr<Wind>& wind : winds) {
      if (wind->isInside(sprite.getGlobalBounds())) {
        air_current += wind->velocity;
      }
    }
  }
};

#endif // BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H
