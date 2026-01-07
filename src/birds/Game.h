#ifndef BIRDSARESWAG_GAME_H
#define BIRDSARESWAG_GAME_H

#include "../abstracts/InputSubscriber.h"
#include "abstracts/AbstractLevel.h"
#include "levels/LevelLibrary.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Game {
public:
  explicit Game(sf::RenderWindow& window_) : window(window_), level(LevelLibrary::current_level) {}
  bool init();
  void render();
  void update(float dt);

private:
  sf::RenderWindow& window;
  std::shared_ptr<AbstractLevel>& level;
};

#endif // BIRDSARESWAG_GAME_H
