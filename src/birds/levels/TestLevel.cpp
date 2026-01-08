#include "TestLevel.h"
void TestLevel::load() {
  surfaces.emplace_back(std::vector<sf::Vector2f>({
      {  50,  250},
      {-250,  250},
      {-300,  000},
      {-200, -200},
      { 000, -325},
      { 325, -450},
      { 475,  000},
      { 250,  200}
  }));
  player_spawn = {200, 50};

  AbstractLevel::load();
}
