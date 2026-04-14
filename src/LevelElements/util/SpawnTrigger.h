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
      AbstractLevelElement* new_things = template_object->makeCopy();
      new_things->destroy_on_load = true;
      LevelLibrary::current_level->addElement(new_things);
    }
  }

  void spawn() override {
    done = false;
  }
};

#endif // BIRDSARESWAG_SPAWN_TRIGGER_H
