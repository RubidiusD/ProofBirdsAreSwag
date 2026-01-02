#ifndef BIRDSARESWAG_ABSTRACTCHOICE_H
#define BIRDSARESWAG_ABSTRACTCHOICE_H

#include "../managers/ActionManager.h"
#include <vector>

class AbstractChoice {
public:
  explicit AbstractChoice(const std::shared_ptr<AbstractAction>& action_) {
    action = action_;
  }
  explicit AbstractChoice(AbstractAction* action_) {
    action = std::make_shared<AbstractAction>(*action_);
  }
  std::shared_ptr<AbstractAction> action;
  unsigned short availability = 1;

  bool choose();

  struct Choices {
    std::vector<AbstractChoice> choices;
    bool onlyOne = true;

    bool choose(unsigned short index);

    Choices(AbstractChoice* choices_, unsigned short total) {
      for (unsigned short i = 0; i != total; i ++) {
        choices.emplace_back(choices_[i]);
      }
    }
    Choices(AbstractChoice* choices_, unsigned short total, bool only_one) {
      for (unsigned short i = 0; i != total; i ++) {
        choices.emplace_back(choices_[i]);
      }
      onlyOne = only_one;
    }
  };
};

#endif // BIRDSARESWAG_ABSTRACTCHOICE_H
