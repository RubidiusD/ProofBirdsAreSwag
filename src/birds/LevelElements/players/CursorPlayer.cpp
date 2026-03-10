#include "CursorPlayer.h"
#include "../../../managers/AssetManager.h"

void CursorPlayer::update(float dt) {

}

void CursorPlayer::initialise() {
  AssetManager::RegisterTexture("Data/images/cursors.png", 2);
  sprite.setTexture(AssetManager::getTexture(2));
  sprite.setTextureRect({0, 0, 16, 16});
}

void CursorPlayer::Point(const Vector2f& vector) {
  setPosition(vector);
}

bool CursorPlayer::collidesSurface() const {
  return false;
}
