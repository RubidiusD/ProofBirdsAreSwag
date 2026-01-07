#include "MainMenu.h"

MainMenu::MainMenu() : AbstractMenu("MAIN") {

}

void MainMenu::load() {
  AbstractMenu::load();
  AssetManager::RegisterTexture("Data/images/TextBox.png", 1);

  buttons.emplace_back(new LoadLevelButton("Test Level", {0, 1, 0, 1}, {0.5, 0.3}, 0));
  buttons.emplace_back(new CloseGameButton({0, 1, 0, 1}, {0.5, 0.85}));
}
