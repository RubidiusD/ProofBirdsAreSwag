#include "ProgressTrigger.h"
#include "../../levels/LevelLibrary.h"

void ProgressTrigger::onSpecificTrigger() {
  if (index > target) {
    target = index;
    LevelLibrary::current_level->publishProgress(UNFINISHED);
  }
}
