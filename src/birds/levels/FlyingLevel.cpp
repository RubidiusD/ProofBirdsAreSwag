#include "FlyingLevel.h"
#include "../abstracts/LevelElements/BirdPlayer.h"

void FlyingLevel::load() {
  surfaces.emplace_back(std::vector<sf::Vector2f>({
      { 050,  050},
      {-250,  050},
      {-300, -500},
      {5000, -700},
      {5200,  325},
      {2525,  360},
      { 475,  180},
      { 050,  470}
  }));
  player_spawn = {0, 0};
  player = std::make_shared<BirdPlayer>();
  winds.emplace_back(std::make_shared<Wind>(sf::Vector2f(32.0f, -3.0f)));

  AbstractLevel::load();
}
