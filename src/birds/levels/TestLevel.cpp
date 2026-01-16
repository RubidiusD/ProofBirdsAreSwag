#include "TestLevel.h"
void TestLevel::load() {
  surfaces.emplace_back(std::vector<sf::Vector2f>({
      {  50,  250},
      {-210,  300},
      {-250,  250},
      {-300,  100},
      {-283,  027},
      {-139,  077},
      {-118,  055},
      {-159, -021},
      {-200, -150},
      { 000, -325},
      { 240, -291},
      { 309, -245},
      { 312, -117},
      { 272, -122},
      { 239, -112},
      { 264, -076},
      { 325, -073},
      { 475,  000},
      { 384,  136},
      { 250,  200},
      { 120,  260}
  }));
  surfaces.emplace_back(std::vector<sf::Vector2f>({
      { 27,  50},
      {135,  74},
      { 77,   0},
      { 57, -20},
      {-23,   0},
  }));
  player_spawn = {200, 50};
  player = std::make_shared<AbstractPlayer>();
  winds.emplace_back(std::make_shared<AbstractWind>(sf::Vector2f(-9/6.0f, 12.0f)));

  AbstractLevel::load();
}
