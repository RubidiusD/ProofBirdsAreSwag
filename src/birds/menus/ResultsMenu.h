#ifndef BIRDSARESWAG_RESULTS_MENU_H
#define BIRDSARESWAG_RESULTS_MENU_H

#include "../../abstracts/AbstractMenu.h"
#include <vector>

struct Attempt {
  float duration = 0.0f;
  unsigned progress = 0;

  Attempt(float d, unsigned p) {duration = d; progress = p;}
};

class ResultsMenu : public AbstractMenu {
protected:
  std::vector<Attempt> attempts;
public:
  ResultsMenu() : AbstractMenu("RSMU") {}
  void AddAttempt(float duration, unsigned progress);
  void CleanseAttempts();
  void load() override;
  void open() override;
  void close() override;

  static void Register();
  static std::shared_ptr<ResultsMenu> instance;
};

#endif // BIRDSARESWAG_RESULTS_MENU_H
