#ifndef BIRDSARESWAG_RESULTS_MENU_H
#define BIRDSARESWAG_RESULTS_MENU_H

#include "../../abstracts/AbstractMenu.h"
#include <vector>

struct Attempt {
  float duration = 0.0f;
  unsigned progress = 0;
  sf::String look_nice() const {
    int minutes = (int)floorf(duration / 60.0f);
    int seconds = (int)floorf(duration - (float)minutes);
    std::string minutes_string = std::to_string(minutes);
    std::string seconds_string = std::to_string(seconds);
    std::string milliseconds_string = std::to_string((int)floorf((duration - (float)minutes - float(seconds)) * 1000.0f));
    while (seconds_string.length() != 2) seconds_string = "0" + seconds_string;
    while (milliseconds_string.length() != 3) milliseconds_string = "0" + milliseconds_string;

    return minutes_string + ":" + seconds_string + "." + milliseconds_string;
  }

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
