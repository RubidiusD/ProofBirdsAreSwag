#ifndef BIRDSARESWAG_RESULTS_MENU_H
#define BIRDSARESWAG_RESULTS_MENU_H

#include "../../abstracts/AbstractMenu.h"
#include <vector>

struct Attempt {
  float duration = 0.0f;
  int progress = 0;
};

class ResultsMenu : public AbstractMenu {
protected:
  static std::vector<Attempt> attempts;
public:
  ResultsMenu() : AbstractMenu("RSMU") {}
  static void AddAttempt(float duration, int progress);
  static void CleanseAttempts();
  void load() override;
  void open() override;
  void close() override;
};

#endif // BIRDSARESWAG_RESULTS_MENU_H
