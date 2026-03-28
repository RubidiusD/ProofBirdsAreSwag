#include "PauseMenu.h"

PauseMenu::PauseMenu() : AbstractMenu("PAUS") {

}

void PauseMenu::load() {
  AbstractMenu::load();

  buttons.emplace_back(new CloseMenuButton("Resume", {0, 1, 0, 2}, {0.5, 0.45}));
  buttons.emplace_back(new OptOutButton("Opt Out", {0, 2, 0, 2}, {0.5, 0.55}));
  buttons.emplace_back(new ResetLevelButton("Reset Level DEBUG DO NOT USE IF I FORGOT TO REMOVE THIS PLEASE TELL ME!!", {1, 2, 0, 2}, {0.5, 0.75}));
//  buttons.emplace_back(new LoadMenuButton("Main Menu", {2, 3, 0, 3}, {0.5, 0.75}, "MAIN"));
}

void PauseMenu::Pause(bool down) {
  if (down) {
    MenuManager::closeMenu();
    LevelLibrary::resumeLevel(false);
  }
}
