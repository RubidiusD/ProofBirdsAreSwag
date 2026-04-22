#include "PauseMenu.h"
#include "../managers/AssetManager.h"
#include "../managers/SoundManager.h"

PauseMenu::PauseMenu() : AbstractMenu("PAUS") {

}

void PauseMenu::load() {
  AbstractMenu::load();

  buttons.emplace_back(new CloseMenuButton("Resume", {0, 1, 0, 3}, {0.5, 0.45}));
  buttons.emplace_back(new OptOutButton("Opt Out", {0, 2, 0, 3}, {0.5, 0.55}));
  buttons.emplace_back(new ControllerButton({1, 3, 0, 3}, {0.5, 0.65}));
  buttons.emplace_back(new ResetLevelButton("Reset Level DEBUG DO NOT USE IF I FORGOT TO REMOVE THIS PLEASE TELL ME!!", {2, 3, 0, 3}, {0.5, 0.8}));

  addText(sf::Color::Black, 0, 24, "Pause Menu", {0.5f, 0.25f});
}
void PauseMenu::open() {
  AbstractMenu::open();
  SoundManager::play(50);
}

void PauseMenu::close() {
  AbstractMenu::close();
  SoundManager::play(51);
}

void PauseMenu::Pause(bool down) {
  if (down) {
    MenuManager::closeMenu();
    LevelLibrary::resumeLevel(false);
  }
}
