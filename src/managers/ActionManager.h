#ifndef BIRDSARESWAG_ACTIONMANAGER_H
#define BIRDSARESWAG_ACTIONMANAGER_H

#include "../abstracts/AbstractAction.h"
#include <SFML/System/Clock.hpp>
#include <list>
#include <memory>

class ActionManager {
public:
  static void update(float dt);
  static void addToTop(const std::shared_ptr<AbstractAction>& action);
  static void addToBot(const std::shared_ptr<AbstractAction>& action);
  static void addToBot(AbstractAction* action_);
private:
  static sf::Clock clock;
  static std::shared_ptr<AbstractAction> currentAction;
  static std::list<std::shared_ptr<AbstractAction>> actionStack;

  static bool refresh();
};

#endif // BIRDSARESWAG_ACTIONMANAGER_H
