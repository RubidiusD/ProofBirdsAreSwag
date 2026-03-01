#include "Egg.h"
#include "../../managers/AssetManager.h"

Egg::Egg(const Vector2f& pos, const Vector2f& vel) {
  setPosition(pos, true);
  velocity = vel;
}

void Egg::initialise() {
  AbstractCircle::initialise();

  sprite.setTexture(AssetManager::getTexture(110));
}
