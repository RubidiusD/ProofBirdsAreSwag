#ifndef BIRDSARESWAG_ABSTRACT_LINE_H
#define BIRDSARESWAG_ABSTRACT_LINE_H

#include "../AbstractLevelElement.h"

class AbstractLine : public AbstractLevelElement {
protected:
  Vector2f pos1;
  Vector2f pos2;
  Vector2f dir1;
  Vector2f dir2;

  bool fire_once = true;
  bool primed = false;
  bool triggered = false;
  bool positive = false;
public:
  AbstractLine(const Vector2f& pos1_, const Vector2f& pos2_);

  void spawn() override;
  void update(float dt) override;
  virtual void onSpecificTrigger() = 0;
};

#endif // BIRDSARESWAG_ABSTRACT_LINE_H
