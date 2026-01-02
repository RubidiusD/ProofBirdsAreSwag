#ifndef BIRDSARESWAG_ABSTRACTPLAYER_H
#define BIRDSARESWAG_ABSTRACTPLAYER_H

#include "../../abstracts/AbstractChoice.h"
#include "../chips/ChipGroup.h"
#include <memory>

using Choices = AbstractChoice::Choices;

class AbstractPlayer {
public:
  unsigned short left_index;
  unsigned short right_index;
  std::shared_ptr<AbstractPlayer> left;
  std::shared_ptr<AbstractPlayer> right;

  std::shared_ptr<ChipGroup> pot;
  std::shared_ptr<ChipGroup> bag;
  std::shared_ptr<ChipGroup> masterBag;
  std::shared_ptr<Chip> drops[2];
  unsigned short rubies = 1;
  unsigned short points = 0;
  unsigned short money = 0;
  unsigned short rat = 0;
  unsigned short index = 0;

  unsigned short safe_distance = 0;
  unsigned short safe_total = 7;
  unsigned short base_safe_total = 7;

  void initialise(unsigned short player_index);
  virtual void makeChoice(const std::shared_ptr<Choices>& choices);
};

static std::vector<std::shared_ptr<AbstractPlayer>> Players = std::vector<std::shared_ptr<AbstractPlayer>>();

#endif // BIRDSARESWAG_ABSTRACTPLAYER_H
