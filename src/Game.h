#ifndef BIRDSARESWAG_GAME_H
#define BIRDSARESWAG_GAME_H

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
};

#endif // BIRDSARESWAG_GAME_H
