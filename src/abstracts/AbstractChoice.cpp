#include "AbstractChoice.h"

bool AbstractChoice::choose() {
  ActionManager::addToBot(action);
  return -- availability == 0;
}

bool AbstractChoice::Choices::choose(unsigned short index) {
  if (choices[index].choose()) {
    if (onlyOne || choices.size() == 1) {
      return true;
    }
    for (; index != choices.size() - 1; index ++) {
      choices[index] = choices[index + 1];
    }
    choices.pop_back();
  }
  return false;
}
