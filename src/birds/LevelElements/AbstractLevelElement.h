#ifndef BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H
#define BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H

#include "../../Settings.h"
#include "../../Vector2f.hpp"
#include "scenery/AbstractWind.h"
#include "scenery/Surface.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

class AbstractLevelElement {
protected:
  sf::Sprite sprite;
  Vector2f velocity;
  Vector2f air_current;
  Vector2f spawn_location;

public:
  explicit AbstractLevelElement(const Vector2f& spawn) {
    spawn_location = spawn;
  }

  std::shared_ptr<CircleCollider> hB;

  bool alive = true;
  bool destroy_on_load = false;

  virtual void update(float dt) { sprite.move(velocity * dt); }
  virtual void render() { S::Window.draw(sprite); }
  virtual void initialise() { setPosition(spawn_location); }
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
  virtual bool circleCollide(const std::shared_ptr<CircleCollider>& rhs) const { return (rhs->c.disSqr(getPosition()) <= rhs->r * rhs->r); }
  virtual Vector2f getPosition() const { return sprite.getPosition(); }
  virtual void setPosition(const Vector2f& p) { sprite.setPosition(p); }
  virtual void spawn() { setPosition(spawn_location); }
  virtual bool collidesPlayer() const { return false; }
  virtual void onHitPlayer() { }
  virtual bool collidesSurface() const { return false; }
  virtual void onHitSurface(const std::shared_ptr<Collision>& collision) { }
  virtual AbstractLevelElement* makeCopy() const { return new AbstractLevelElement({}); }
  virtual AbstractLevelElement* makeCopy(const Vector2f& spawn_) const { return new AbstractLevelElement(spawn_); }
};

#endif // BIRDSARESWAG_ABSTRACT_LEVEL_ELEMENT_H
