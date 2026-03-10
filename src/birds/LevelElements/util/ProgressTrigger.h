#ifndef BIRDSARESWAG_PROGRESS_TRIGGER_H
#define BIRDSARESWAG_PROGRESS_TRIGGER_H

#include "AbstractLine.h"
class ProgressTrigger : public AbstractLine {
protected:
  unsigned index;
  unsigned& target;
public:
  ProgressTrigger(unsigned& t, const Vector2f& pos1_, const Vector2f& pos2_, unsigned i) : AbstractLine(pos1_, pos2_), target(t) {
    index = i;
    fire_once = true;
  }
  void onSpecificTrigger() override {
    if (index > target) {
      target = index;
    }
  }
};

#endif // BIRDSARESWAG_PROGRESS_TRIGGER_H
