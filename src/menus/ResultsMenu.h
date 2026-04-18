#ifndef BIRDSARESWAG_RESULTS_MENU_H
#define BIRDSARESWAG_RESULTS_MENU_H

#include "../LevelElements/enemies/AbstractBird.h"
#include "../LevelElements/util/ProgressData.h"
#include "../MathLib.h"
#include "AbstractMenu.h"
#include <ntdef.h>
#include <vector>

class ResultsMenu : public AbstractMenu {
protected:
  std::vector<Attempt> attempts;
public:
  ResultsMenu() : AbstractMenu("RSMU") {}
  void AddChapter(const Chapter& new_attempt);
  void SaveAndCleanseAttempts();
  void load() override;
  void open() override;
  void close() override;

  static void Register();
  static std::shared_ptr<ResultsMenu> instance;
  static std::vector<std::shared_ptr<AbstractBird>> birds;
  static std::shared_ptr<AbstractBird> bird;
};

#endif // BIRDSARESWAG_RESULTS_MENU_H
