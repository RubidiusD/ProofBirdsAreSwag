#ifndef BIRDSARESWAG_LEVEL_LIBRARY_H
#define BIRDSARESWAG_LEVEL_LIBRARY_H

#include "../../abstracts/AbstractAction.h"
#include "../abstracts/AbstractLevel.h"
class LevelLibrary {
public:
  static std::vector<std::shared_ptr<AbstractLevel>> levels;
  static std::shared_ptr<AbstractLevel> current_level;
  static void loadLevel(AbstractLevel* level);
  static bool isLoading;
  static bool setLevel(unsigned index);

  class LoadLevelAction : public AbstractAction {
  private:
    unsigned index;
    static const float duration;

  public:
    explicit LoadLevelAction(unsigned menu_index) : AbstractAction("LoadLevelAction") {
      index = menu_index;
      timer = duration;
    }
    void end() override;
  };
};

#endif // BIRDSARESWAG_LEVEL_LIBRARY_H
