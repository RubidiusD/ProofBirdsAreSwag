#include "PauseMenu.h"

PauseMenu::PauseMenu() : AbstractMenu("PAUS") {

}

void PauseMenu::load() {
  AbstractMenu::load();

  buttons.emplace_back(new CloseMenuButton("Resume", {0, 1, 0, 2}, {0.5, 0.4}));
  buttons.emplace_back(new ResetLevelButton("Reset Level", {0, 2, 0, 2}, {0.5, 0.5}));
  buttons.emplace_back(new LoadMenuButton("Main Menu", {1, 2, 0, 2}, {0.5, 0.75}, "MAIN"));
}

void PauseMenu::Pause(bool down) {
  if (down) {
    MenuManager::closeMenu();
    LevelLibrary::resumeLevel(false);
  }
}
