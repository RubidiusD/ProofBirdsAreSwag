#ifndef BIRDSARESWAG_CURSOR_PLAYER_H
#define BIRDSARESWAG_CURSOR_PLAYER_H

#include "AbstractPlayer.h"

class CursorPlayer : public AbstractPlayer {
public:
  CursorPlayer(const Vector2f& spawn, Chapter& c) : AbstractPlayer(spawn, c) {}

  void initialise() override;
  void update(float dt) override;
  void Point(const Vector2f& vector) override;
  bool collidesSurface() const override;
};

#endif // BIRDSARESWAG_CURSOR_PLAYER_H
