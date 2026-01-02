#ifndef BIRDSARESWAG_SETTINGS_H
#define BIRDSARESWAG_SETTINGS_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class S {
public:
  enum DLC {
    Vanilla,
    HerbWitches,
    Alchemists
  };

  static bool dlc[3];
  static bool rubiTweaks;
  static bool CursorMode;
  static bool CursorDown;

  static sf::RenderWindow Window;
  static sf::Vector2f Res;
};

#endif // BIRDSARESWAG_SETTINGS_H
