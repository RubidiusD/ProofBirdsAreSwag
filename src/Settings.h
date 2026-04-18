#ifndef BIRDSARESWAG_SETTINGS_H
#define BIRDSARESWAG_SETTINGS_H

#include "Vector2f.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class S {
public:
  static bool CursorDown;
  static bool ControllerConnected;
  static bool ControllerRecent;
  static unsigned player_index;
  static Vector2f mouse;

  static sf::RenderWindow Window;
  static Vector2f Res;
  static Vector2f ScreenSize;
  static sf::View UI_View;
  static const float stick_tolerance;
};

#endif // BIRDSARESWAG_SETTINGS_H
