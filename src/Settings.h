#ifndef BIRDSARESWAG_SETTINGS_H
#define BIRDSARESWAG_SETTINGS_H

#include "Vector2f.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class S {
public:
  static bool CursorMode;
  static bool CursorDown;
  static bool Controller;
  static bool ControllerRecent;
  static unsigned player_index;
  static Vector2f mouse;

  static bool bird2;
  static bool bird3;
  static bool bird4;

  static sf::RenderWindow Window;
  static Vector2f Res;
  static Vector2f ScreenSize;
  static sf::View UI_View;
  static const float stick_tolerance;
};

#endif // BIRDSARESWAG_SETTINGS_H
