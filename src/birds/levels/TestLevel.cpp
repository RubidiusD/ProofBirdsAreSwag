#include "TestLevel.h"
void TestLevel::load() {
  surfaces.emplace_back(std::vector<sf::Vector2f>({
      { 0000, -1000},
      {-1000, -1000},
      {-1200,    00},
      { -800,   800},
      {   00,  1300},
      { 1500,  1800},
      { 1900,    00},
      {  700,  -700}
  }));

  AbstractLevel::load();
}
