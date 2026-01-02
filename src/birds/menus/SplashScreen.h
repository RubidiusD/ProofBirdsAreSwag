#ifndef BIRDSARESWAG_SPLASHSCREEN_H
#define BIRDSARESWAG_SPLASHSCREEN_H

#include "../../abstracts/AbstractMenu.h"
#include <SFML/Graphics/Text.hpp>

class SplashScreen : public AbstractMenu {
public:
  SplashScreen();
  bool keyPressed(sf::Keyboard::Key key, bool down) override;
  void render() override;
  void load() override;
private:
  sf::Text Title;
  sf::Sprite UWE_Logo;
};

#endif // BIRDSARESWAG_SPLASHSCREEN_H
