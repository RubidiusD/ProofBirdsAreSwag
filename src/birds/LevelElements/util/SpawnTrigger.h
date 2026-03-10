#ifndef BIRDSARESWAG_SPAWN_TRIGGER_H
#define BIRDSARESWAG_SPAWN_TRIGGER_H

#include "../../levels/LevelLibrary.h"
#include "AbstractBox.h"

class SpawnTrigger : public AbstractBox {
protected:
  std::shared_ptr<AbstractLevelElement> template_object;
  bool done = false;
public:
  SpawnTrigger(const sf::FloatRect& bounds_, const std::shared_ptr<AbstractLevelElement>& tmpl) : AbstractBox(bounds_) {
    template_object = tmpl;
  }

  void onHitPlayer() override {
    if (!done) {
      done = true;
      printf("triggering lol \n");
      LevelLibrary::current_level->addElement(template_object->makeCopy());
      printf("element added \n");
    }
  }

  void spawn() override {
    done = false;
  }
};

#endif // BIRDSARESWAG_SPAWN_TRIGGER_H
