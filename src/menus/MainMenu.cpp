#include "MainMenu.h"
#include "PauseMenu.h"

MainMenu::MainMenu() : AbstractMenu("MAIN") {

}

void MainMenu::load() {
  AbstractMenu::load();
  AssetManager::RegisterTexture("Data/images/TextBox.png", 1);

//  buttons.emplace_back(new LoadLevelButton("Test Level", {0, 1, 0, 4}, {0.5, 0.2}, 0));
//  buttons.emplace_back(new LoadLevelButton("Flying Level", {0, 2, 0, 4}, {0.5, 0.3}, 1));
  buttons.emplace_back(new LoadLevelButton("Tracking Level", {0, 1, 0, 3}, {0.5, 0.3}, 2));
  buttons.emplace_back(new ControllerButton({0, 2, 0, 3}, {0.5, 0.5}));
  buttons.emplace_back(new CloseGameButton({1, 2, 0, 3}, {0.5, 0.75}));
  buttons.emplace_back(new PlayerIndexButton({0, 2, 0, 0}, {0.8f, 0.5f}));

  addText(sf::Color::White, 0, 16, ": Move", {0.3f, 0.9f});
  addText(sf::Color::White, 0, 16, ": Jump", {0.8f, 0.9f});

  AssetManager::RegisterTexture("Data/images/WASD.png", 21);
  AssetManager::RegisterTexture("Data/images/Space.png", 22);
  AssetManager::RegisterTexture("Data/images/LStick.png", 23);
  AssetManager::RegisterTexture("Data/images/AButton.png", 24);

  WASD     .setTexture(AssetManager::getTexture(21));
  Space    .setTexture(AssetManager::getTexture(22));
  LeftStick.setTexture(AssetManager::getTexture(23));
  AButton  .setTexture(AssetManager::getTexture(24));
  WASD     .setPosition(S::Res.operator*({0.225f, 0.9f}));
  Space    .setPosition(S::Res.operator*({0.725f, 0.9f}));
  LeftStick.setPosition(S::Res.operator*({0.225f, 0.9125f}));
  AButton  .setPosition(S::Res.operator*({0.725f, 0.9125f}));
  WASD     .setOrigin(20, 11);
  Space    .setOrigin(20, 11);
  LeftStick.setOrigin(16, 16);
  AButton  .setOrigin(16, 16);
  WASD     .setScale(2, 2);
  Space    .setScale(2, 2);
  LeftStick.setScale(2, 2);
  AButton  .setScale(2, 2);
  WASD     .setTextureRect({0, 0, 39, 23});
  Space    .setTextureRect({0, 0, 39, 23});
}

void MainMenu::update(float dt) {
  AbstractMenu::update(dt);

  if (!S::ControllerRecent) {
    float prev = anim_timer;
    anim_timer += dt;
    if (anim_timer >= 1.0f) {
      anim_timer -= 1.0f;
      Space.setTextureRect({0, 0, 39, 23});
      WASD .setTextureRect({0, 0, 39, 23});
    }
    else {if (anim_timer > 0.5f && prev < 0.5f) {
        Space.setTextureRect({0, 23, 39, 23});
      }
      WASD.setTextureRect({0, ((int)(anim_timer * 8)) * 23, 39, 23});
    }
  }
}

void MainMenu::render() {
  AbstractMenu::render();

  if (S::ControllerRecent) {
    S::Window.draw(LeftStick);
    S::Window.draw(AButton);
  }
  else {
    S::Window.draw(WASD);
    S::Window.draw(Space);
  }
}
