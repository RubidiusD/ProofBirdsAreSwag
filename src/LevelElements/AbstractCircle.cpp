#include "AbstractCircle.h"
#include "../levels/LevelLibrary.h"
#include "fx/Particle.h"

bool AbstractCircle::surfaceCollide(Surface& surface) {
  std::shared_ptr<Collision> collision = surface.CollideCircle(hB);
  if (collision != nullptr && !snapTo(collision, collision->collisionTheSecond) && (floor == nullptr || (collision->edge != floor && collision->edge != floor->prev && collision->edge != floor->next))) {
    onHitSurface(collision);

    return true;
  }
  return false;
}

void AbstractCircle::onHitSurface(const std::shared_ptr<Collision>& collision) {
  if (floor != nullptr && collision->edge != nullptr) {
//    //  printf("doin both \n");
    std::shared_ptr<Collision> collision1 = floor->CollideCircle(hB);
    if (floor->dire.dot(collision->edge->norm) > 0.0f) {
      snapTo(collision, collision1);
    }
    else {
      snapTo(collision1, collision);
    }
  }
  else {
    snapTo(collision);
  }
}

void AbstractCircle::setPosition(const Vector2f& pos) {
  AbstractLevelElement::setPosition(pos);
  hB->c = pos;
}

void AbstractCircle::stickToFloor() {
  if (floor != nullptr) {
    std::shared_ptr<Collision> cA = floor->concave ? floor->prev->CollideCircle(hB) : nullptr;
    std::shared_ptr<Collision> cB = floor->CollideCircle(hB);
    std::shared_ptr<Collision> cC = floor->next->concave ? floor->next->CollideCircle(hB) : nullptr;

    if (cB == nullptr) { // no longer touching or in line with current floor
      if (!(cA != nullptr && cA->inRange && snapTo(cA)) && !(cC != nullptr && cC->inRange && snapTo(cC))) {
        unsetFloor(floor);
        coyote = max_coyote;
      }
    }
    else {
      if (!(cA != nullptr && cA->inRange && snapTo(cA, cB)) && !(cC != nullptr && cC-> inRange && snapTo(cB, cC))) {
        snapTo(cB);
      }
    }
  }
}

void AbstractCircle::initialise() {
  AbstractLevelElement::initialise();
}

bool AbstractCircle::snapTo(const std::shared_ptr<Collision>& collision) {
  if (collision == nullptr) {
    coyote = max_coyote;
    return false;
  }
  coyote_normal.set(0, 0);
  Vector2f old_vel = velocity;
  velocity = velocity.splat(collision->normal, collision->elasticity(elasticity));
  if (can_stick) {
    bool wasntStuck = floor == nullptr;
    if (setFloor(floor, collision->edge) && wasntStuck)
      onStick();
    else if (wasntStuck)
      onBounce();
    sprite.setColor(sf::Color::White);
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
  if (!c2->edge->concave) {
    return snapTo(c2);
  }
  coyote_normal.set(0, 0);
  Edge* e1 = c1->edge;
  Edge* e2 = c2->edge;
  float divisor = e2->dire.x * e1->dire.y - e2->dire.y * e1->dire.x;
  if (divisor != 0) {
    setPosition(e2->point + e2->dire * (hB->r * ((e1->dire.x*(e2->norm.y - e1->norm.y) - e1->dire.y*(e2->norm.x - e1->norm.x)) / divisor)) + e2->norm * hB->r);
  }
  Vector2f old_vel = velocity;
  float E1 = c1->elasticity(elasticity);
  float E2 = c2->elasticity(elasticity);
  Vector2f a = velocity.splat(e1->norm, E1).splat(e2->norm, E2);
  Vector2f b = velocity.splat(e2->norm, E2).splat(e1->norm, E1);
  velocity = (M::lengthSQ(a) > M::lengthSQ(b)) ? a : b;

  if (!setFloor(floor, e1)) {
    setFloor(floor, e2);
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
  unsetFloor(floor);
  sprite.setColor(sf::Color::White);
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
  velocity = Vector2f{(u3.x+u4.x+r*u4.x-r*u3.x) / 2, u3.y}.unRotate(c3) / c3.magSqr();
  rhs->velocity = Vector2f{(u4.x+u3.x+r*u3.x-r*u4.x) / 2, u4.y}.unRotate(c3) / c3.magSqr();
}

void AbstractCircle::tickCoyote(float dt) {
  if (can_stick && floor == nullptr && coyote != 0.0f) {
    coyote = fmaxf(coyote - dt, 0.0f);
  }
}
