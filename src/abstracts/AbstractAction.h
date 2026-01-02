#ifndef BIRDSARESWAG_ABSTRACTACTION_H
#define BIRDSARESWAG_ABSTRACTACTION_H

#include <memory>

class AbstractAction {
public:
  virtual void start() {};
  virtual void update(float dt) {};
  virtual void end() {};
  virtual void tick(float dt);

  float timer = 0.0f;
  bool isDone = false;

  unsigned short target = 0;
  int amount = 0;
};

#endif // BIRDSARESWAG_ABSTRACTACTION_H
