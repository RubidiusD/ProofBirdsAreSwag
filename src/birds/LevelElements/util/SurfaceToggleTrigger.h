#ifndef BIRDSARESWAG_SURFACE_TOGGLE_TRIGGER_H
#define BIRDSARESWAG_SURFACE_TOGGLE_TRIGGER_H

#include "AbstractBox.h"

class SurfaceToggleTrigger : public AbstractBox {
protected:
  bool toggle;
  bool done = false;
  Surface& surface;
public:
  SurfaceToggleTrigger(Surface& surface_to_toggle, bool target_toggle, const sf::FloatRect& rect) : AbstractBox(rect), surface(surface_to_toggle) {
    toggle = target_toggle;
  }

  bool collidesPlayer() const override {
    return !done;
  }

  void spawn() override {
    printf("Spawning a surface toggle trigger \n");
    done = false;
  }

  void onHitPlayer() override {
    done = true;
    surface.active = toggle;
  }
};

#endif // BIRDSARESWAG_SURFACE_TOGGLE_TRIGGER_H
