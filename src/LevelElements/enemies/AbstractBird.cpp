#include "AbstractBird.h"
#include "../../levels/LevelLibrary.h"
#include "../../managers/AssetManager.h"
#include "../../managers/SoundManager.h"

bool AbstractBird::collidesPlayer() const {
  return true;
}

AbstractLevelElement *AbstractBird::makeCopy(const Vector2f &spawn_) const {
  return new AbstractBird(spawn_);
}

AbstractLevelElement *AbstractBird::makeCopy() const {
  return new AbstractBird(spawn_location);
}

void AbstractBird::initialise() {
  AbstractCircle::initialise();

  AssetManager::RegisterTexture("Data/images/Particles3.png", 101);
  AssetManager::RegisterTexture("Data/images/EggParticles.png", 102);
  AssetManager::RegisterTexture("Data/images/Egg.png", 110);
  AssetManager::RegisterTexture("Data/images/Bird1.png", 111);
  AssetManager::RegisterTexture("Data/images/BirdWingSheet.png", 113);
  sprite.setTexture(AssetManager::getTexture(111));
  sprite.setOrigin(29, 12);
  wing.setTexture(AssetManager::getTexture(113));
  setWingRect({0, 0, 29, 27});
  wing.setOrigin(23, 5);
  LevelLibrary::current_level->addListener(&playerPredictor);
  can_stick = false;
}

void AbstractBird::render() {
  S::Window.draw(sprite);
  S::Window.draw(wing);
}

void AbstractBird::setPosition(const Vector2f& pos) {
  hB->c = pos;
  sprite.setPosition(pos);
  wing.setPosition(pos);
}

void AbstractBird::remove() {
  LevelLibrary::current_level->removeListener(playerPredictor);
}

bool AbstractBird::isAimGood(const Vector2f& v) {
  eggPredictor.setCoefficient(0, getPosition());
  eggPredictor.setCoefficient(1, v);
  eggPredictor.setCoefficient(2, (air_current + Vector2f{0, 640.0f}) / 2);

  return eggPredictor.nearest(playerPredictor, 0.2f) < 256.0f;
}

void AbstractBird::considerEgg() {
  Vector2f firing_velocity = velocity;
  firing_velocity.y += jump_strength;
  if (egg_cooldown == 0.0f && (spray != 0 || isAimGood(firing_velocity))) {
    LevelLibrary::current_level->addElement(new Egg(getPosition(), firing_velocity));
    SoundManager::play(hB->c, 20, 22, 1.0f, 0.1f);
    if (spray == 1) {
      egg_cooldown = egg_max_cooldown;
      spray = 0;
    }
    else if (spray == 0) {
      egg_cooldown = egg_between_cooldown;
      spray = max_spray - 1;
    }
    else {
      egg_cooldown = egg_between_cooldown;
      spray --;
    }
  }
}

void AbstractBird::tickWing(float dt) {
  anim_cooldown -= dt;
  float facing = (wing_direction.x > 0) ? 1 : -1;
  switch (wingRect.top) {
  case (27):
    velocity += Vector2f{0, -air_acceleration_speed * dt * flap_cooldown};
    break;
  case (54):
    velocity += Vector2f{facing * 0.89508196721f, -0.44590163934f} * dt * air_acceleration_speed * flap_cooldown;
    break;
  case (81):
    velocity += Vector2f{facing * 0.980198019802f, 0.19801980198f} * dt * air_acceleration_speed * flap_cooldown;
    break;
  }
  if (anim_cooldown <= 0.0f) {
    anim_cooldown = 0.125f;
    if (wingRect.left == 87) {
      setWingRect({0, 0, 29, 27});
    }
    else {
      wingRect.left += 29;
      setWingRect(wingRect);
    }
  }
}

void AbstractBird::setWingRect(const sf::IntRect& rect) {
  wingRect = rect;
  wing.setTextureRect(rect);
}
