#include "Bird3.h"
#include "../../../managers/AssetManager.h"
#include "../../levels/LevelLibrary.h"

const float Bird3::ELASTIC = 0.75f;
const float Bird3::AIR_ACCELERATION = 1536.0f;
const float Bird3::RADIUS = 12.0f;
const float Bird3::DRAG = 0.5f;

void Bird3::initialise() {
  AbstractCircle::initialise();

  AssetManager::RegisterTexture("Data/images/Particles3.png", 101);
  AssetManager::RegisterTexture("Data/images/EggParticles.png", 102);
  AssetManager::RegisterTexture("Data/images/Egg.png", 110);
  AssetManager::RegisterTexture("Data/images/Bird1.png", 111);
  sprite.setTexture(AssetManager::getTexture(111));
  sprite.setOrigin(29, 12);
  LevelLibrary::current_level->addListener(&playerPredictor);

  elasticity = ELASTIC;
  air_acceleration_speed = AIR_ACCELERATION;
  drag_modifier = DRAG;
  hB->r = RADIUS;
}

void Bird3::applyWind(const std::vector<std::shared_ptr<AbstractWind>> &winds) {
  AbstractCircle::applyWind(winds);
}

void Bird3::remove() {
  LevelLibrary::current_level->removeListener(playerPredictor);
}

void Bird3::update(float dt) {
  selfPredictor.QuarryIs(getPosition(), dt);

  velocity += (playerPredictor.f(0.5f) + Vector2f{0.0f, 100.0f} - selfPredictor.f(0.5f)).norm() * air_acceleration_speed * dt;
  air_current -= velocity;
  velocity += air_current * drag_modifier * dt;
  setPosition(velocity * dt + sprite.getPosition());

  cooldowns(dt);

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

bool Bird3::isAimGood(const Vector2f& v) {
  eggPredictor.setCoefficient(0, getPosition());
  eggPredictor.setCoefficient(1, v);
  eggPredictor.setCoefficient(2, (air_current / 2 + Vector2f{0, 640.0f}) / 2);

  return eggPredictor.nearest(playerPredictor, 0.2f) < 256.0f;
}

void Bird3::cooldowns(float dt) {
  if (egg_cooldown != 0.0f) {
    egg_cooldown -= dt;
    if (egg_cooldown <= 0.0f) {
      egg_cooldown = 0.0f;
    }
  }
}

AbstractLevelElement* Bird3::makeCopy(const Vector2f& spawn_) const {
  return new Bird3(spawn_);
}
AbstractLevelElement* Bird3::makeCopy() const {
  return new Bird3(spawn_location);
}

bool Bird3::collidesPlayer() const {
  return true;
}
