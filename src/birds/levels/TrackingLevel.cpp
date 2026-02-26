#include "TrackingLevel.h"
#include "../LevelElements/Bird2.h"
#include "../LevelElements/CursorPlayer.h"

void TrackingLevel::load() {
  surfaces.emplace_back(std::vector<Vector2f>({
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
  surfaces.emplace_back(std::vector<Vector2f>({
      { 27,  50},
      {135,  74},
      { 77,   0},
      { 57, -20},
      {-23,   0},
  }));
  player = std::make_shared<AbstractPlayer>();
  player_spawn.set(150.0f, -30.0f);
  addListener(new Bird2());
  elements.back()->moveTo(-150.0f, -30.0f);
  view.setCenter(0, 0);

  AbstractLevel::load();
}

void TrackingLevel::open() {
  S::Window.setMouseCursorVisible(false);
  AbstractLevel::open();
}

void TrackingLevel::Pause(bool down) {
  AbstractLevel::Pause(down);
  if (down) {
    S::Window.setMouseCursorVisible(true);
  }
}

void TrackingLevel::close() {
  S::Window.setMouseCursorVisible(true);
  AbstractLevel::close();
}

//void TrackingLevel::render() {
//  S::Window.clear(sf::Color::White);
//  S::Window.setView(view);
//  player->render();
//  for (Surface& surface : surfaces) {
//    surface.render();
//  }
//  for (std::shared_ptr<AbstractLevelElement>& element : elements) {
//    element->render();
//  }
//}

void TrackingLevel::Point(const Vector2f &vector) {
  player->Point(S::Window.mapPixelToCoords(sf::Vector2i(vector), view));
}
