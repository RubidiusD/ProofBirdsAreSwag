#ifndef BIRDSARESWAG_RESULTS_MENU_H
#define BIRDSARESWAG_RESULTS_MENU_H

#include "../../MathLib.h"
#include "../../abstracts/AbstractMenu.h"
#include "../LevelElements/util/ProgressData.h"
#include <ntdef.h>
#include <vector>

class ResultsMenu : public AbstractMenu {
protected:
  std::vector<Attempt> attempts;
public:
  ResultsMenu() : AbstractMenu("RSMU") {}
  void AddChapter(unsigned p, float d, unsigned h, float s, unsigned j, unsigned c, unsigned b, unsigned l, ProgressType t);
  void AddChapter(const Chapter& new_attempt);
  void CleanseAttempts();
  void load() override;
  void open() override;
  void close() override;

  static void Register();
  static std::shared_ptr<ResultsMenu> instance;
};

#endif // BIRDSARESWAG_RESULTS_MENU_H
