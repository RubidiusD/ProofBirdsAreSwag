#ifndef BIRDSARESWAG_END_LEVEL_TRIGGER_H
#define BIRDSARESWAG_END_LEVEL_TRIGGER_H

#include "../../levels/LevelLibrary.h"
#include "../../managers/MenuManager.h"
#include "AbstractBox.h"

class EndLevelTrigger : public AbstractBox {
protected:
  unsigned ID = AbstractMenu::makeID("RSMU");
  sf::RectangleShape rectangle;
public:
  explicit EndLevelTrigger(const sf::FloatRect& bounds_) : AbstractBox(bounds_) {
    rectangle.setPosition(bounds.left, bounds.top);
    rectangle.setSize({bounds.width, bounds.height});
    rectangle.setFillColor({0, 255, 0, 100});
  }

  void render() override {
    S::Window.draw(rectangle);
  }

  void onHitPlayer() override {
    LevelLibrary::current_level->publishProgress(WON);
    LevelLibrary::setLevel(-1);
    MenuManager::setMenu(ID);
  }
};

#endif // BIRDSARESWAG_END_LEVEL_TRIGGER_H
