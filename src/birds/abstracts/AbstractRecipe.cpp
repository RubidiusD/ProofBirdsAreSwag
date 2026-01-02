#include "../chips/ChipLibrary.h"
#include "AbstractPlayer.h"

unsigned short AbstractRecipe::calculatePosition(unsigned short player_index, const std::shared_ptr<Chip>& chip) {
  std::shared_ptr<Chip> last = Players[player_index]->pot->lastChip();
  return last->position + chip->value + ChipLibrary::recipes[last->colour]->modifyNext(player_index, last, chip) + modifySelf(player_index, chip);
}

/* ---- ignore below the line ---- */

void AbstractRecipe::obtain(unsigned short player_index, int tier) {
  Players[player_index]->bag->addChip(make(tier));
  Players[player_index]->bag->shuffle();
}

void AbstractRecipe::purchase(unsigned short player_index, int tier) {
  obtain(player_index, tier);
  Players[player_index]->money -= prices[tier].c;
}

std::shared_ptr<Chip> AbstractRecipe::make(unsigned short index) const {
  return std::make_shared<Chip>(Chip::Stats(colour, prices[index].v, prices[index].c, index));
}

std::vector<std::shared_ptr<Chip>> AbstractRecipe::makeAll() const {
  std::vector<std::shared_ptr<Chip>> new_chips;
  for (int index = 0; index != 3; index ++) {
    if (prices[index].exists()) {
      new_chips.emplace_back(make(index));
      continue;
    }
    break;
  }
  return new_chips;
}

void AbstractRecipe::addToBot(const std::shared_ptr<AbstractAction>& action) {
  ActionManager::addToBot(action);
}

void AbstractRecipe::addToTop(const std::shared_ptr<AbstractAction>& action) {
  ActionManager::addToTop(action);
}

bool AbstractRecipe::owns() const {
  return S::dlc[required];
}

bool AbstractRecipe::canUpgrade(unsigned short tier) const {
  return (tier != 2 && prices[tier + 1].exists());
}

void AbstractRecipe::upgrade(const std::shared_ptr<Chip>& chip) const {
  chip->tier ++;
  chip->value = prices[chip->tier].v;
  chip->price = prices[chip->tier].c;
}
