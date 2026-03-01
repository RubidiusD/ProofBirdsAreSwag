#include "Bird2.h"
#include "../../managers/AssetManager.h"
#include "../levels/LevelLibrary.h"

const float Bird2::ELASTIC = 0.75f;
const float Bird2::GRAVITY = 384.0f;
const float Bird2::ACCELERATION = 512.0f;
const float Bird2::AIR_ACCELERATION = 0.0f;
const float Bird2::JUMP = 180.0f;
const float Bird2::RADIUS = 12.0f;
const float Bird2::DRAG = 1.0f;

void Bird2::render() {
  AbstractCircle::render();
  for (sf::Sprite& sprite : predictions) {
    S::Window.draw(sprite);
  }
}

void Bird2::initialise() {
  AbstractCircle::initialise();

  AssetManager::RegisterTexture("Data/images/Particles3.png", 101);
  AssetManager::RegisterTexture("Data/images/Egg.png", 110);
  for (auto & prediction : predictions) {
    prediction.setTexture(AssetManager::getTexture(101));
    prediction.setTextureRect({0, 0, 2, 2});
  }
  AssetManager::RegisterTexture("Data/images/Bird1.png", 111);
  AssetManager::RegisterTexture("Data/images/Bird1W.png", 112);
  sprite.setTexture(AssetManager::getTexture(111));
  sprite.setOrigin(29, 12);
  LevelLibrary::current_level->addListener(&playerPredictor);

  elasticity = ELASTIC;
  gravity = GRAVITY;
  acceleration_speed = ACCELERATION;
  air_acceleration_speed = AIR_ACCELERATION;
  jump_strength = JUMP;
  radius = RADIUS;
  drag_modifier = DRAG;
}

void Bird2::remove() {
  LevelLibrary::current_level->removeListener(playerPredictor);
}

void Bird2::update(float dt) {
  for (int index = 1; index != 11; index ++) {
    predictions[index - 1].setPosition(playerPredictor.f((float)index / 20.0f));
  }

  selfPredictor.QuarryIs(getPosition(), dt);

  velocity.y += gravity * dt;
  air_current -= velocity;
  velocity += air_current * drag_modifier * dt;

  cooldowns(dt);

  if (flap_cooldown == 0.0f) {
    flap();
  }

  moveTo(velocity * dt + sprite.getPosition());

  if (egg_cooldown == 0.0f && isAimGood()) {
    LevelLibrary::current_level->addEgg(getPosition(), velocity);
    egg_cooldown = egg_max_cooldown;
  }
}

bool Bird2::isAimGood() {
  return false;
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
