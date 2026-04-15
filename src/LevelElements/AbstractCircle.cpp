#include "AbstractCircle.h"
#include "../levels/LevelLibrary.h"
#include "fx/Particle.h"

bool AbstractCircle::surfaceCollide(Surface& surface) {
  std::shared_ptr<Collision> collision = surface.CollideCircle(hB);
  if (collision != nullptr && collision->edge != floor1 && collision->edge != floor2) {
    onHitSurface(collision);

    return true;
  }
  return false;
}

void AbstractCircle::onHitSurface(const std::shared_ptr<Collision>& collision) {
  snapTo(collision);
}

void AbstractCircle::setPosition(const Vector2f& pos) {
  AbstractLevelElement::setPosition(pos);
  hB->c = pos;
}

void AbstractCircle::stickToFloor() {
  if (floor1 != nullptr) {
    if (floor2 == nullptr) {
      std::shared_ptr<Collision> cA = floor1->concave ? floor1->prev->CollideCircle(hB) : nullptr;
      std::shared_ptr<Collision> cB = floor1->CollideCircle(hB);
      std::shared_ptr<Collision> cC = floor1->next->concave ? floor1->next->CollideCircle(hB) : nullptr;

      if (cB == nullptr) { // no longer touching or in line with current floor1
        if (!(cA != nullptr && cA->inRange && snapTo(cA)) && !(cC != nullptr && cC->inRange && snapTo(cC))) {
          unsetFloor(floor1);
          coyote = max_coyote;
        }
      }
      else {
        if (!(cA != nullptr && cA->inRange && snapTo(cA, cB)) && !(cC != nullptr && cC-> inRange && snapTo(cB, cC))) {
          snapTo(cB);
        }
      }
    }
    else {
      std::shared_ptr<Collision> cA = floor1->CollideCircle(hB);
      std::shared_ptr<Collision> cB = floor2->CollideCircle(hB);

      if (cA == nullptr && cB == nullptr) {
        unsetFloor(floor1);
        unsetFloor(floor2);
        coyote = max_coyote;
      }
      else if ((cA == nullptr || !cA->inRange) && cB != nullptr && cB->inRange) {
        snapTo(cB);
      }
      else if ((cB == nullptr || !cB->inRange) && cA != nullptr && cA->inRange) {
        snapTo(cA);
      }
      else if (cB->inRange && cA->inRange) {
        snapTo(cA, cB);
      }
      else {
        Vector2f dire = velocity.norm();
        Vector2f floor1Dire = floor1->direN * -1.0;
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

void AbstractCircle::initialise() {
  AbstractLevelElement::initialise();
}

bool AbstractCircle::snapTo(const std::shared_ptr<Collision>& collision) {
  if (collision == nullptr) {
//    coyote = max_coyote;
    return false;
  }
  coyote_normal.set(0, 0);
  Vector2f old_vel = velocity;
  velocity = velocity.splat(collision->normal, collision->elasticity(elasticity));
  if (can_stick) {
    if (setFloor(floor1, collision->edge))
      onStick();
    else
      onBounce();
    unsetFloor(floor2);
  }
  setPosition(collision->point + collision->normal * hB->r);
  float change = M::distanceSQ(old_vel, velocity);
  if (change > 1000.0f) {
    LevelLibrary::current_level->spawnParticle(4, collision->point, velocity - old_vel);
    LevelLibrary::current_level->spawnParticle(4, collision->point, collision->normal * change);
  }
  return true;
}

bool AbstractCircle::snapTo(const std::shared_ptr<Collision>& c1, const std::shared_ptr<Collision>& c2) {
  if (c1 == nullptr || c2 == nullptr) {
    coyote = max_coyote;
    return false;
  }
  coyote_normal.set(0, 0);
  Edge* e1 = c1->edge;
  Edge* e2 = c2->edge;
  setPosition(e1->chop(hB->r));

  float E1 = c1->elasticity(elasticity);
  float E2 = c2->elasticity(elasticity);
  Vector2f a = velocity.splat(e1->norm, E1).splat(e2->norm, E2);
  Vector2f b = velocity.splat(e2->norm, E2).splat(e1->norm, E1);
  Vector2f old_vel = velocity;
  velocity = (M::lengthSQ(a) > M::lengthSQ(b)) ? a : b;
  if (setFloor(floor1, e1)) {
    setFloor(floor2, e2);
  }
  else {
    setFloor(floor1, e2);
  }
  float change = M::distanceSQ(old_vel, velocity);
  if (change > 1000.0f) {
    for (unsigned index = 0; index != 2; index ++) {
      LevelLibrary::current_level->addElement(new Particle(c1->point, c1->normal.rotate(Vector2f(1.0f, M::Randf(-2.0f, 2.0f)).norm()) * (1.0f + (float)M::Rand(0, 80) / 100.0f) * change));
      LevelLibrary::current_level->addElement(new Particle(c2->point, c2->normal.rotate(Vector2f(1.0f, M::Randf(-2.0f, 2.0f)).norm()) * (1.0f + (float)M::Rand(0, 80) / 100.0f) * change));
    }
  }

  return true;
}

bool AbstractCircle::setFloor(Edge*& receptacle, Edge* new_edge) const {
  if (new_edge == nullptr || new_edge->norm.dot(velocity) > S::stick_tolerance) {
    receptacle = nullptr;
    return false;
  }

  receptacle = new_edge;
  return true;
}

void AbstractCircle::unsetFloor(Edge*& receptacle) {
  if (receptacle == nullptr) {
    return;
  }
  if (coyote_normal.is(0.0f, 0.0f)) {
    coyote_normal = receptacle->norm;
  }
  else {
    coyote_normal += receptacle->norm;
    coyote_normal /= 2.0f;
  }
  receptacle = nullptr;
}

void AbstractCircle::applyWind(const std::vector<std::shared_ptr<AbstractWind>>& winds) {
  air_current.x = 0.0f; air_current.y = 0.0f;
  for (const std::shared_ptr<AbstractWind>& wind : winds) {
    if (wind->isInside(hB)) {
      air_current += wind->velocity;
    }
  }
}

void AbstractCircle::spawn() {
  setPosition(spawn_location);
  velocity.set(0.0f, 0.0f);
  unsetFloor(floor1);
  unsetFloor(floor2);
}

void AbstractCircle::onHitPlayer() {
  std::shared_ptr<AbstractPlayer> player = LevelLibrary::current_level->getPlayer();
  Vector2f midPoint = player->hB->c.avg(hB->c);
  Vector2f normal = (player->hB->c - hB->c).norm();
  setPosition(midPoint - normal * hB->r);
  player->setPosition(midPoint + normal * player->hB->r);
  bounceOff(player);
}

bool AbstractCircle::collidesSurface() const {
  return true;
}

void AbstractCircle::bounceOff(const std::shared_ptr<AbstractCircle>& rhs) {
  Vector2f c3 = (rhs->hB->c-hB->c).conj();
  Vector2f u3 = velocity.rotate(c3);
  Vector2f u4 = rhs->velocity.rotate(c3);
  float r = (elasticity + rhs->elasticity) / 2;
  velocity = Vector2f{(u3.x+u4.x+r*u4.x-r*u3.x) / (2), u3.y}.unRotate(c3) / c3.magSqr();
  rhs->velocity = Vector2f{(u4.x+u3.x+r*u3.x-r*u4.x) / (2), u4.y}.unRotate(c3) / c3.magSqr();
}

void AbstractCircle::tickCoyote(float dt) {
  if (can_stick && floor1 == nullptr && coyote != 0.0f) {
    coyote = fmaxf(coyote - dt, 0.0f);
  }
}
