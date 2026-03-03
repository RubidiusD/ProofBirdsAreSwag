#ifndef BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H
#define BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H

#include "../../Settings.h"
#include "../../Vector2f.hpp"
#include "../LevelElements/Surface.h"
#include "AbstractWind.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class AbstractLevelElement {
protected:
  sf::Sprite sprite;
  Vector2f velocity;
  Vector2f air_current;

public:
  bool alive = true;

  virtual void update(float dt) { sprite.move(velocity * dt); }
  virtual void render() { S::Window.draw(sprite); }
  virtual void initialise() {}
  virtual void moveTo(const Vector2f& pos) {sprite.setPosition(pos);}
  virtual void moveTo(float x, float y) {sprite.setPosition(x, y);}
  virtual void applyWind(const std::vector<std::shared_ptr<AbstractWind>>& winds) {
    air_current.x = 0.0f; air_current.y = 0.0f;
    for (const std::shared_ptr<AbstractWind>& wind : winds) {
      if (wind->isInside(sprite.getGlobalBounds())) {
        air_current += wind->velocity;
      }
    }
  }
  virtual void remove() {}
  virtual bool surfaceCollide(Surface& surface) { return true; }
  virtual bool circleCollide(const Vector2f& c, float r) const { return (c.disSqr(getPosition()) <= r * r); }
  virtual Vector2f getPosition() const { return sprite.getPosition(); }
};

#endif // BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H
