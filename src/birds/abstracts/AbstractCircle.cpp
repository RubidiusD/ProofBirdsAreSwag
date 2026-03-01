#include "AbstractCircle.h"
#include "../../MathLib.h"
#include "../LevelElements/Particle.h"
#include "../levels/LevelLibrary.h"

bool AbstractCircle::surfaceCollide(Surface& surface) {
  std::shared_ptr<Collision> collision = surface.CollideCircle(getPosition(), radius);
  if (collision != nullptr && collision->edge != floor && collision->edge != floor2) {
    snapTo(collision);

    return true;
  }
  return false;
}

void AbstractCircle::setPosition(const Vector2f& pos) {
  setPosition(pos, false);
}

void AbstractCircle::setPosition(const Vector2f& pos, bool override) {
  if (override || M::distanceSQ(getPosition(), pos) < 400) {
    moveTo(pos);
  }
}

void AbstractCircle::stickToFloor() {
  if (floor != nullptr) {
    if (floor2 == nullptr) {
      std::shared_ptr<Collision> cA = floor->prev->CollideCircle(getPosition(), radius);
      std::shared_ptr<Collision> cB = floor->CollideCircle(getPosition(), radius);
      std::shared_ptr<Collision> cC = floor->next->CollideCircle(getPosition(), radius);

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
      std::shared_ptr<Collision> cA = floor->CollideCircle(getPosition(), radius);
      std::shared_ptr<Collision> cB = floor2->CollideCircle(getPosition(), radius);

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
        Vector2f dire = velocity.norm();
        Vector2f floor1Dire = floor->direN * -1.0;
        Vector2f floor2Dire = floor2->direN;

        if (dire.dot(floor1Dire) > dire.dot(floor2Dire)) {
          snapTo(cA);
        }
        else {
          snapTo(cB);
        }
      }
    }
  }
}

Vector2f AbstractCircle::getPosition() const {
  return sprite.getPosition();
}

bool AbstractCircle::snapTo(const std::shared_ptr<Collision>& collision) {
  if (collision == nullptr) {
    return false;
  }
  Vector2f old_vel = velocity;
  velocity = velocity.splat(collision->normal, collision->elasticity(elasticity));
  if (collision->normal.y < max_steepness) {
    setFloor(floor, collision->edge);
    unsetFloor(floor2);
  }
  setPosition(collision->point + collision->normal * radius);
  float change = M::distanceSQ(old_vel, velocity);
  if (change > 1000.0f) {
    LevelLibrary::current_level->spawnParticle(4, collision->point, velocity - old_vel);
    LevelLibrary::current_level->spawnParticle(4, collision->point, collision->normal * change);
  }
  return true;
}

bool AbstractCircle::snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2) {
  if (c1 == nullptr || c2 == nullptr) {
    return false;
  }
  Edge* e1 = c1->edge;
  Edge* e2 = c2->edge;
  setPosition(e1->chop(radius));

  float E1 = c1->elasticity(elasticity);
  float E2 = c2->elasticity(elasticity);
  Vector2f a = velocity.splat(e1->norm, E1).splat(e2->norm, E2);
  Vector2f b = velocity.splat(e2->norm, E2).splat(e1->norm, E1);
  Vector2f old_vel = velocity;
  velocity = (M::lengthSQ(a) > M::lengthSQ(b)) ? a : b;
  if (setFloor(floor, e1)) {
    setFloor(floor2, e2);
  }
  else {
    setFloor(floor, e2);
  }
  float change = M::distanceSQ(old_vel, velocity);
  if (change > 1000.0f) {
    for (unsigned index = 0; index != 2; index ++) {
      LevelLibrary::current_level->addElement(new Particle(c1->point, c1->normal * Vector2f(1.0f, M::Randf(-2.0f, 2.0f)).norm() * (1.0f + (float)M::Rand(0, 80) / 100.0f) * change, 0.3f));
      LevelLibrary::current_level->addElement(new Particle(c2->point, c2->normal * Vector2f(1.0f, M::Randf(-2.0f, 2.0f)).norm() * (1.0f + (float)M::Rand(0, 80) / 100.0f) * change, 0.3f));
    }
  }

  return true;
}

bool AbstractCircle::setFloor(Edge*& receptacle, Edge* new_edge) const {
  if (new_edge == nullptr || new_edge->norm.dot(velocity) > S::stick_tolerance) {
    receptacle = nullptr;
    return false;
  }

  if (new_edge->norm.y < max_steepness) {
    receptacle = new_edge;
    return true;
  }
  else {
    receptacle = nullptr;
    return false;
  }
}

void AbstractCircle::unsetFloor(Edge*& receptacle) const {
  receptacle = nullptr;
}

void AbstractCircle::applyWind(const std::vector<std::shared_ptr<AbstractWind>>& winds) {
  air_current.x = 0.0f; air_current.y = 0.0f;
  for (const std::shared_ptr<AbstractWind>& wind : winds) {
    if (wind->isInside(getPosition(), radius)) {
      air_current += wind->velocity;
    }
  }
}
