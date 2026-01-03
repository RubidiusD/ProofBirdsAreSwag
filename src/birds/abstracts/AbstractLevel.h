#ifndef BIRDSARESWAG_ABSTRACT_LEVEL_H
#define BIRDSARESWAG_ABSTRACT_LEVEL_H

#include "AbstractPlayer.h"
#include <vector>

class AbstractLevel {
protected:
  std::vector<Surface> surfaces;
  std::shared_ptr<AbstractPlayer> player;

public:
  void update(float dt);
  void render();

  bool active = false;
};

#endif // BIRDSARESWAG_ABSTRACT_LEVEL_H
