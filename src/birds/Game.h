#ifndef BIRDSARESWAG_GAME_H
#define BIRDSARESWAG_GAME_H

#include "abstracts/AbstractLevel.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Game {
public:
  explicit Game(sf::RenderWindow& window_) : window(window_) {}
  bool init();
  void render();
  void update(float dt);

private:
  sf::RenderWindow& window;
  std::vector<std::shared_ptr<AbstractLevel>> level_library;
  std::shared_ptr<AbstractLevel> current_level;
};

#endif // BIRDSARESWAG_GAME_H
