#include "MainMenu.h"
#include "PauseMenu.h"

MainMenu::MainMenu() : AbstractMenu("MAIN") {

}

void MainMenu::load() {
  AbstractMenu::load();
  AssetManager::RegisterTexture("Data/images/TextBox.png", 1);

  buttons.emplace_back(new LoadLevelButton("Test Level", {0, 1, 0, 4}, {0.5, 0.2}, 0));
  buttons.emplace_back(new LoadLevelButton("Flying Level", {0, 2, 0, 4}, {0.5, 0.3}, 1));
  buttons.emplace_back(new LoadLevelButton("Tracking Level", {1, 3, 0, 4}, {0.5, 0.4}, 2));
  buttons.emplace_back(new ControllerButton({2, 4, 0, 4}, {0.5, 0.5}));
  buttons.emplace_back(new CloseGameButton({3, 4, 0, 4}, {0.5, 0.75}));

  addText(sf::Color::White, 0, 16, ": Move", {0.3f, 0.9f});
  addText(sf::Color::White, 0, 16, ": Jump", {0.8f, 0.9f});
}
