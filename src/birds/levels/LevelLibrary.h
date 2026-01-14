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
  static bool resumeLevel(bool reset);

  class LoadLevelAction : public AbstractAction {
    unsigned index;
    static const float duration;
  public:
    explicit LoadLevelAction(unsigned menu_index);
    void end() override;
  };

  class ResumeLevelAction : public AbstractAction {
    static const float duration;
    bool r;
  public:
    explicit ResumeLevelAction(bool reset);
    void end() override;
  };
};

#endif // BIRDSARESWAG_LEVEL_LIBRARY_H
