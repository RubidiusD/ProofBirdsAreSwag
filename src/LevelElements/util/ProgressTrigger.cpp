#include "ProgressTrigger.h"
#include "../../levels/LevelLibrary.h"
#include "../../managers/SoundManager.h"

void ProgressTrigger::onSpecificTrigger() {
  if (index > target) {
    target = index;
    LevelLibrary::current_level->publishProgress(UNFINISHED);
    SoundManager::play(30, 0.3f, 0.05f);
  }
}
