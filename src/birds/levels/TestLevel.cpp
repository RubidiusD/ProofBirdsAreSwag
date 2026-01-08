#include "TestLevel.h"
void TestLevel::load() {
  surfaces.emplace_back(std::vector<sf::Vector2f>({
      { 100,  500},
      {-500,  500},
      {-600,  000},
      {-400, -400},
      { 000, -650},
      { 750, -900},
      { 950,  000},
      { 500,  400}
  }));

  AbstractLevel::load();
}
