#include "Bird2.h"
#include "../../../managers/AssetManager.h"
#include "../../levels/LevelLibrary.h"

const float Bird2::ELASTIC = 0.75f;
const float Bird2::GRAVITY = 384.0f;
const float Bird2::ACCELERATION = 512.0f;
const float Bird2::AIR_ACCELERATION = 0.0f;
const float Bird2::JUMP = 256.0f;
const float Bird2::RADIUS = 12.0f;
const float Bird2::DRAG = 1.0f;

void Bird2::initialise() {
  AbstractCircle::initialise();

  AssetManager::RegisterTexture("Data/images/Particles3.png", 101);
  AssetManager::RegisterTexture("Data/images/EggParticles.png", 102);
  AssetManager::RegisterTexture("Data/images/Egg.png", 110);
  AssetManager::RegisterTexture("Data/images/Bird1.png", 111);
  sprite.setTexture(AssetManager::getTexture(111));
  sprite.setOrigin(29, 12);
  LevelLibrary::current_level->addListener(&playerPredictor);

  elasticity = ELASTIC;
  gravity = GRAVITY;
  acceleration_speed = ACCELERATION;
  air_acceleration_speed = AIR_ACCELERATION;
  jump_strength = JUMP;
  drag_modifier = DRAG;
  hB->r = RADIUS;
}

void Bird2::applyWind(const std::vector<std::shared_ptr<AbstractWind>> &winds) {
  AbstractCircle::applyWind(winds);
}

void Bird2::remove() {
  LevelLibrary::current_level->removeListener(playerPredictor);
}

void Bird2::update(float dt) {
  selfPredictor.QuarryIs(getPosition(), dt);

  velocity.y += gravity * dt;
  air_current -= velocity;
  velocity += air_current * drag_modifier * dt;

  cooldowns(dt);

  if (spray == 0 && flap_cooldown == 0.0f) {
    flap();
  }

  setPosition(velocity * dt + sprite.getPosition());

  Vector2f firing_velocity = velocity;
  firing_velocity.y += jump_strength;

  if (egg_cooldown == 0.0f && (spray != 0 || isAimGood(firing_velocity))) {
    LevelLibrary::current_level->addElement(new Egg(getPosition(), firing_velocity));
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

bool Bird2::isAimGood(const Vector2f& v) {
  eggPredictor.setCoefficient(0, getPosition());
  eggPredictor.setCoefficient(1, v);
  eggPredictor.setCoefficient(2, (air_current / 2 + Vector2f{0, 640.0f}) / 2);

  return eggPredictor.nearest(playerPredictor, 0.2f) < 256.0f;
}

void Bird2::cooldowns(float dt) {
  if (flap_cooldown != 0.0f) {
    flap_cooldown -= dt;
    if (flap_cooldown <= 0.0f) {
      flap_cooldown = 0.0f;
    }
  }
  if (egg_cooldown != 0.0f) {
    egg_cooldown -= dt;
    if (egg_cooldown <= 0.0f) {
      egg_cooldown = 0.0f;
    }
  }
}

void Bird2::flap() {
  Vector2f cur = getPosition();
  Vector2f tar = playerPredictor.current_position();
  Vector2f pre = selfPredictor.f(0.5f);
  Vector2f tarp = playerPredictor.f(0.5f);

  Vector2f change;
       if (cur.x < tar.x - 50.0f && pre.x < tarp.x + 25.0f) { change.set( 0.8f, -0.6f); }
  else if (cur.x > tar.x + 50.0f && pre.x > tarp.x - 25.0f) { change.set(-0.8f, -0.6f); }
  else if (cur.y > tar.y - 75.0f && pre.y > tarp.y - 100.0f) { change.set( 0.0f, -1.0f); }
  if (change.y != 0.0f) {
    change *= jump_strength;
    flap_cooldown = flap_max_cooldown;
    LevelLibrary::current_level->spawnParticle(8, cur, change * -1.0f);
    velocity += change;
  }
}

AbstractLevelElement* Bird2::makeCopy(const Vector2f& spawn_) const {
  return new Bird2(spawn_);
}
AbstractLevelElement* Bird2::makeCopy() const {
  return new Bird2(spawn_location);
}

bool Bird2::collidesPlayer() const {
  return true;
}
