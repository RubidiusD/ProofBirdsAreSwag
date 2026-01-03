#include "AbstractLevel.h"

void AbstractLevel::update(float dt) {
  if (active) {
    player->update(dt);
  }
}

void AbstractLevel::render() {
  if (active) {
    player->render();
  }
}
