#include "ActionManager.h"

void ActionManager::update(float dt) {
  if (currentAction != nullptr && currentAction->isDone) {
    currentAction = nullptr;
  }
  if (refresh()) {
    currentAction->start();
  }
  if (currentAction != nullptr && !currentAction->isDone) {
    currentAction->update(dt);
  }
}

bool ActionManager::refresh() {
  if (currentAction == nullptr && !actionStack.empty()) {
    currentAction = actionStack.front();
    actionStack.pop_front();
    return true;
  }
  return false;
}

void ActionManager::addToTop(const std::shared_ptr<AbstractAction>& action) {
  actionStack.emplace_front(action);
}

void ActionManager::addToBot(const std::shared_ptr<AbstractAction>& action) {
  actionStack.emplace_back(action);
}

void ActionManager::addToBot(AbstractAction *action_) {
  addToBot(std::make_shared<AbstractAction>(*action_));
}

std::shared_ptr<AbstractAction> ActionManager::currentAction = nullptr;
std::list<std::shared_ptr<AbstractAction>> ActionManager::actionStack = std::list<std::shared_ptr<AbstractAction>>();
