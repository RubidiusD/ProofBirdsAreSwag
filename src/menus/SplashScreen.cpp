#include "SplashScreen.h"
#include "../Settings.h"
#include "../managers/AssetManager.h"
#include "../managers/MenuManager.h"

void SplashScreen::KeyPressed(sf::Keyboard::Key key, bool down) {
  MenuManager::setMenu("MAIN");
}

void SplashScreen::Select(bool down) {
  MenuManager::setMenu("MAIN");
}

SplashScreen::SplashScreen() : AbstractMenu("SPSH") {
  AssetManager::RegisterTexture("Data/images/Uwelogo.png", 0);
}

void SplashScreen::load() {
  AbstractMenu::load();
  auto* UWE_Logo = new sf::Sprite();
  UWE_Logo->setTexture(AssetManager::getTexture(0));
  UWE_Logo->setPosition(S::Res.x - UWE_Logo->getGlobalBounds().width, S::Res.y - UWE_Logo->getGlobalBounds().height);
  addDrawable(UWE_Logo);
  addText(sf::Color::White, 0, 36, "Birds are Swag", {0.5f, 0.5f});
}
