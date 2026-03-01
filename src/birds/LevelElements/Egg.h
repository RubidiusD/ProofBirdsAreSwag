#ifndef BIRDSARESWAG_EGG_H
#define BIRDSARESWAG_EGG_H

#include "../abstracts/AbstractCircle.h"

class Egg : public AbstractCircle {
public:
  Egg(const Vector2f& pos, const Vector2f& vel);
  void initialise() override;

private:

};

#endif // BIRDSARESWAG_EGG_H
