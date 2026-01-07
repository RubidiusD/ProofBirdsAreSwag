#include "AbstractAction.h"
#include <cstdio>

void AbstractAction::tick(float dt) {
  timer -= dt;
  if (timer <= 0) {
    isDone = true;
  }
}

void AbstractAction::identify() const {
  printf("%s \n", identity.c_str());
}
