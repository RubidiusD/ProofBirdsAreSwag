#include "TrackingLevel.h"
#include "../LevelElements/Bird2.h"
#include "../LevelElements/CursorPlayer.h"

void TrackingLevel::load() {
  surfaces.emplace_back(std::vector<Vector2f>({
      {  50,  250},
      {-210,  300},
      {-250,  250},
      {-325,  325},
      {-450,  350},
      {-543,  286},
      {-612,  230},
      {-834,  183},
      {-852,  100},
      {-810,  040},
      {-760, -010},
      {-700, -050},
      {-625, -025},
      {-575,  000},
      {-550, -075},
      {-400, -125},
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
  surfaces.emplace_back(std::vector<Vector2f>({
      { 027,  50},
      { 135,  74},
      { 077,  00},
      { 057, -20},
      {-023,  00},
  }));
  surfaces.emplace_back(std::vector<Vector2f>({
      {-340,  072},
      {-300,  140},
      {-283,  101},
      {-139,  117},
      {-118,   95},
      {-159,   19},
  }));
  player = std::make_shared<AbstractPlayer>();
  player_spawn.set(150.0f, -30.0f);
  addElement(new Bird2());
  elements.back()->moveTo(-150.0f, -30.0f);
  winds.emplace_back(new AbstractWind({-60.0f, -10.0f}, 0.5f));

  AbstractLevel::load();
}

void TrackingLevel::open() {
  S::Window.setMouseCursorVisible(false);
  AbstractLevel::open();
}

void TrackingLevel::Pause(bool down) {
  AbstractLevel::Pause(down);
  S::Window.setMouseCursorVisible(down);
}

void TrackingLevel::close() {
  S::Window.setMouseCursorVisible(true);
  AbstractLevel::close();
}

void TrackingLevel::Point(const Vector2f& vector) {
  player->Point(S::Window.mapPixelToCoords(sf::Vector2i(vector), view));
}
