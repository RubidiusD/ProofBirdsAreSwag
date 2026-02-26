#include "Bird2.h"
#include "../../managers/AssetManager.h"
#include "../levels/LevelLibrary.h"

const float Bird2::ELASTIC = 0.75;

void Bird2::render() {
  AbstractCircle::render();
  for (sf::Sprite& sprite : predictions) {
    S::Window.draw(sprite);
  }
}

void Bird2::initialise() {
  AbstractCircle::initialise();

  AssetManager::RegisterTexture("Data/images/Particles.png", 101);
  for (auto & prediction : predictions) {
    prediction.setTexture(AssetManager::getTexture(101));
    prediction.setTextureRect({0, 0, 2, 2});
  }
  AssetManager::RegisterTexture("Data/images/Bird1.png", 111);
  AssetManager::RegisterTexture("Data/images/Bird1W.png", 112);
  AbstractCircle::sprite.setTexture(AssetManager::getTexture(111));

  elasticity = ELASTIC;
}

void Bird2::update(float dt) {
  for (int index = 1; index != 11; index ++) {
    predictions[index - 1].setPosition(f((float)index / 20.0f));
  }

  AbstractCircle::update(dt);

  if (egg_cooldown != 0.0f) {
    egg_cooldown -= dt;
    if (egg_cooldown <= 0.0f) {
      egg_cooldown = 0.0f;
    }
  }

//  if (egg_cooldown == 0.0f && isAimGood()) {
//    LevelLibrary::current_level->addElement(new )
//  }
}

bool Bird2::isAimGood() { return false; }
