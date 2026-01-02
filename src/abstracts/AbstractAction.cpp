#include "AbstractAction.h"
#include <cstdio>

void AbstractAction::tick(float dt) {
  timer -= dt;
  if (timer <= 0) {
    end();
    isDone = true;
  }
}
