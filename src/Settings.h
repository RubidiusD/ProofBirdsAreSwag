#ifndef BIRDSARESWAG_SETTINGS_H
#define BIRDSARESWAG_SETTINGS_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class S {
public:
  static bool CursorMode;
  static bool CursorDown;

  static sf::RenderWindow Window;
  static sf::Vector2f Res;
  static sf::Vector2f ScreenSize;
  static sf::View UI_View;
};

#endif // BIRDSARESWAG_SETTINGS_H
