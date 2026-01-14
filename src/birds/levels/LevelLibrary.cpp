#include "LevelLibrary.h"
#include "../../managers/ActionManager.h"

std::vector<std::shared_ptr<AbstractLevel>> LevelLibrary::levels;
std::shared_ptr<AbstractLevel> LevelLibrary::current_level;

void LevelLibrary::loadLevel(AbstractLevel* level) {
  levels.emplace_back(level);
}

bool LevelLibrary::isLoading = false;

bool LevelLibrary::setLevel(unsigned index) {
  if (isLoading) {
    return false;
  }
  isLoading = true;
  ActionManager::addToBot(std::make_shared<LoadLevelAction>(index));
  return true;
}

const float LevelLibrary::LoadLevelAction::duration = 0.1f;

void LevelLibrary::LoadLevelAction::end() {
  isLoading = false;

  if (current_level != nullptr) {
    current_level->close();
  }
  current_level = levels[index];
  if (!current_level->isLoaded) {
    current_level->load();
    printf("Loaded Level %d \n", index);
  }
  current_level->open();
  printf("Opened Level %d \n", index);
}
