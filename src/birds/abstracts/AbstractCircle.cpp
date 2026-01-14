#include "AbstractCircle.h"
#include "../levels/LevelLibrary.h"
#include "../LevelElements/Particle.h"

bool AbstractCircle::SurfaceCollide(Surface& surface) {
  std::shared_ptr<Collision> collision = surface.CollideCircle(sprite.getPosition(), radius);
  if (collision != nullptr && collision->edge != floor && collision->edge != floor2) {
    sf::Vector2f old_vel = velocity;
    snapTo(collision);
    float change = M::distanceSQ(old_vel, velocity);
    if (change > 0.1f) {
      for (unsigned index = 0; index != 4; index ++) {
        LevelLibrary::current_level->addElement(new Particle(collision->point, M::times(collision->normal, M::norm({1.0f, M::Randf(-2.0f, 2.0f)})) * (100.0f + (float)M::Rand(0, 80)) * change, 0.3f));
      }
    }

    return true;
  }
  return false;
}

void AbstractCircle::setPosition(const sf::Vector2f& pos) {
  setPosition(pos, false);
}

void AbstractCircle::setPosition(const sf::Vector2f& pos, bool override) {
  if (override || M::distanceSQ(sprite.getPosition(), pos) < 400) {
    moveTo(pos);
  }
}

void AbstractCircle::stickToFloor() {
  if (floor != nullptr) {
    if (floor2 == nullptr) {
      std::shared_ptr<Collision> cA = floor->prev->CollideCircle(sprite.getPosition(), radius);
      std::shared_ptr<Collision> cB = floor->CollideCircle(sprite.getPosition(), radius);
      std::shared_ptr<Collision> cC = floor->next->CollideCircle(sprite.getPosition(), radius);

      if (cB == nullptr) { // no longer touching or in line with current floor
        if (!snapTo(cA) && !snapTo(cC)) {
          unsetFloor(floor);
        }
      }
      else {
        if (!(cA != nullptr && cA->inRange && snapTo(cA, cB)) && !(cC != nullptr && cC-> inRange && snapTo(cB, cC))) {
          snapTo(cB);
        }
      }
    }
    else {
      std::shared_ptr<Collision> cA = floor->CollideCircle(sprite.getPosition(), radius);
      std::shared_ptr<Collision> cB = floor2->CollideCircle(sprite.getPosition(), radius);

      if (cA == nullptr && cB == nullptr) {
        unsetFloor(floor);
        unsetFloor(floor2);
      }
      else if (cA == nullptr) {
        snapTo(cB);
      }
      else if (cB == nullptr || (cA->inRange && !cB->inRange)) {
        snapTo(cA);
      }
      else if (cB->inRange && !cA->inRange) {
        snapTo(cB);
      }
      else if (cB->inRange && cA->inRange) {
        snapTo(cA, cB);
      }
      else {
        sf::Vector2f dire = M::norm(velocity);
        sf::Vector2f floor1Dire = M::scale(M::norm(floor->dire), -1.0);
        sf::Vector2f floor2Dire = M::norm(floor2->dire);

        if (M::dot(dire, floor1Dire) > M::dot(dire, floor2Dire)) {
          snapTo(cA);
        }
        else {
          snapTo(cB);
        }
      }
    }
  }
}

sf::Vector2f AbstractCircle::getPosition() const {
  return sprite.getPosition();
}

bool AbstractCircle::snapTo(const std::shared_ptr<Collision>& collision) {
  if (collision == nullptr) {
    return false;
  }
  if (collision->normal.y < max_steepness) {
    setFloor(floor, collision->edge);
    unsetFloor(floor2);
  }
  velocity = M::splat(velocity, collision->normal);
  setPosition(collision->point + M::scale(collision->normal, radius));
  return true;
}

bool AbstractCircle::snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2) {
  if (c1 == nullptr || c2 == nullptr) {
    return false;
  }
  Edge *e1 = c1->edge;
  Edge *e2 = c2->edge;
  setPosition(e2->point + M::scale(e2->dire, radius * ((e1->dire.x*(e2->norm.y - e1->norm.y) - e1->dire.y*(e2->norm.x - e1->norm.x)) /(e2->dire.x * e1->dire.y - e2->dire.y * e1->dire.x))) + M::scale(e2->norm, radius));
  if (setFloor(floor, e1)) {
    setFloor(floor2, e2);
  }
  else {
    setFloor(floor, e2);
  }

  sf::Vector2f a = M::splat(M::splat(velocity, e1->norm), e2->norm);
  sf::Vector2f b = M::splat(M::splat(velocity, e2->norm), e1->norm);
  velocity = (M::lengthSQ(a) > M::lengthSQ(b)) ? a : b;

  return true;
}

bool AbstractCircle::setFloor(Edge*& receptacle, Edge* new_edge) const {
  if (receptacle != nullptr) {
    receptacle->sprite.setColor(sf::Color::Red);
  }
  if (new_edge == nullptr) {
    receptacle = nullptr;
    return false;
  }

  if (new_edge->norm.y < max_steepness) {
    receptacle = new_edge;
    new_edge->sprite.setColor(sf::Color::Green);
    return true;
  }
  else {
    new_edge->sprite.setColor(sf::Color::Blue);
    receptacle = nullptr;
    return false;
  }
}

void AbstractCircle::unsetFloor(Edge*& receptacle) const {
  if (receptacle != nullptr) {
    receptacle->sprite.setColor(sf::Color::Red);
  }
  receptacle = nullptr;
}

void AbstractCircle::applyWind(const std::vector<std::shared_ptr<AbstractWind>>& winds) {
  air_current.x = 0.0f; air_current.y = 0.0f;
  for (const std::shared_ptr<AbstractWind>& wind : winds) {
    if (wind->isInside(sprite.getPosition(), radius)) {
      air_current += wind->velocity;
    }
  }
}
