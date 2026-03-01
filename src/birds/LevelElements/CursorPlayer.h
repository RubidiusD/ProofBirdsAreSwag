#ifndef BIRDSARESWAG_CURSOR_PLAYER_H
#define BIRDSARESWAG_CURSOR_PLAYER_H

#include "../abstracts/AbstractPlayer.h"

class CursorPlayer : public AbstractPlayer {
public:
  void initialise() override;

public:
  void update(float dt) override;
  void Point(const Vector2f &vector) override;
  bool surfaceCollide(Surface &surface) override;
};

#endif // BIRDSARESWAG_CURSOR_PLAYER_H
