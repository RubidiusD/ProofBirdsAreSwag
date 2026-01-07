#ifndef BIRDSARESWAG_ABSTRACTACTION_H
#define BIRDSARESWAG_ABSTRACTACTION_H

#include <SFML/System/String.hpp>
#include <memory>

class AbstractAction {
public:
  virtual void start() {};
  virtual void update(float dt) {};
  virtual void end() {};
  void tick(float dt);
  void identify() const;

  float timer = 0.0f;
  bool isDone = false;
  std::string identity;

  int amount = 0;

  explicit AbstractAction(const sf::String& string) {
    identity = string;
  }
};

#endif // BIRDSARESWAG_ABSTRACTACTION_H
