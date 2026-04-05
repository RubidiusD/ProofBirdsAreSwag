#include "FlyingLevel.h"
#include "../../managers/AssetManager.h"
#include "../LevelElements/players/BirdPlayer.h"

void FlyingLevel::load() {
  surfaces.emplace_back(std::vector<Vector2f>({
      { 050,  050},
      {-250,  050},
      {-300, -500},
      {5000, -700},
      {5200,  325},
      {2525,  660},
      { 475,  580},
      { 070,  670}
  }));
  player = std::make_shared<BirdPlayer>(Vector2f(0, 0), chapter);
  winds.emplace_back(std::make_shared<AbstractWind>(Vector2f(302.0f, -3.0f)));

  AbstractLevel::load();
}
