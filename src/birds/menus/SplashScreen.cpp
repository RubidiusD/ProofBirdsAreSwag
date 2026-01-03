#include "SplashScreen.h"
#include "../../managers/AssetManager.h"
#include "../../managers/MenuManager.h"
#include "../../managers/Settings.h"

bool SplashScreen::keyPressed(sf::Keyboard::Key key, bool down) {
  MenuManager::setMenu("MAIN");
  return true;
}

SplashScreen::SplashScreen() : AbstractMenu("SPSH") {
  AssetManager::RegisterTexture("Data/images/Uwelogo.png", 0);
}

void SplashScreen::load() {
  isLoaded = true;
  auto* UWE_Logo = new sf::Sprite();
  UWE_Logo->setTexture(AssetManager::getTexture(0));
  UWE_Logo->setPosition(S::Res.x - UWE_Logo->getGlobalBounds().width, S::Res.y - UWE_Logo->getGlobalBounds().height);
  addDrawable(UWE_Logo);
  auto* Title = new sf::Text();
  Title->setCharacterSize(52);
  Title->setFont(AssetManager::getFont(0));
  Title->setString("Birds are Swag");
  Title->setPosition((S::Res.x - Title->getGlobalBounds().width) / 2, (S::Res.y - Title->getGlobalBounds().height) / 2);
  Title->setFillColor(sf::Color::White);
  addDrawable(Title);
}
