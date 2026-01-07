#ifndef BIRDSARESWAG_LEVEL_LOADER_HPP
#define BIRDSARESWAG_LEVEL_LOADER_HPP

#include "../Game.h"
#include "LevelLibrary.h"
#include "TestLevel.h"

namespace LevelLoader {
  void LoadLevels() {
    LevelLibrary::loadLevel(new TestLevel());
  }
}

#endif // BIRDSARESWAG_LEVEL_LOADER_HPP
