#include "AbstractLine.h"
#include "../../levels/LevelLibrary.h"

AbstractLine::AbstractLine(const Vector2f& pos1_, const Vector2f& pos2_) : AbstractLevelElement(pos1_) {
  pos1 = pos1_;
  pos2 = pos2_;
  dir1 = pos2 - pos1;
  dir2 = dir1.i();
}

void AbstractLine::spawn() {
  primed = false;
  triggered = false;
}

void AbstractLine::update(float dt) {
  if (triggered && fire_once)
    return;
  Vector2f c = LevelLibrary::current_level->getPlayer()->hB->c;
  float t2 = (c.y*dir1.x - c.x*dir1.y + pos1.x*dir1.y - pos1.y*dir1.x) / (dir1.x*dir2.y - dir1.y*dir2.x);
  float t1 = (dir1.x == 0) ? (c.y - dir2.y*t2 - pos1.y) / dir1.y : (c.x - dir2.x*t2 - pos1.x) / dir1.x;
  if (positive != (t2 > 0)) {
    positive = !positive;
    if (primed && t1 >= 0 && t1 <= 1) {
      triggered = true;
      primed = false;
      onSpecificTrigger();
    }
  }
  if (!primed && (!fire_once || !triggered)) {
    primed = true;
  }
}
