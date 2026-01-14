#ifndef BIRDSARESWAG_LEVEL_LOADER_HPP
#define BIRDSARESWAG_LEVEL_LOADER_HPP

#include "../Game.h"
#include "FlyingLevel.h"
#include "LevelLibrary.h"
#include "TestLevel.h"

namespace LevelLoader {
  void LoadLevels() {
    LevelLibrary::loadLevel(new TestLevel());
    LevelLibrary::loadLevel(new FlyingLevel());
  }
}

#endif // BIRDSARESWAG_LEVEL_LOADER_HPP
