#ifndef BIRDSARESWAG_TRACKING_LEVEL_H
#define BIRDSARESWAG_TRACKING_LEVEL_H

#include "AbstractLevel.h"

class TrackingLevel : public AbstractLevel {
public:
  void load() override;

private:
  void Point(const Vector2f& vector) override;

public:
  void open() override;
  void close() override;
  void Pause(bool down) override;
};

#endif // BIRDSARESWAG_TRACKING_LEVEL_H
