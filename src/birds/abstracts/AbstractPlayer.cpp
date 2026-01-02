#include "AbstractPlayer.h"
#include "../chips/ChipLibrary.h"

void AbstractPlayer::makeChoice(const std::shared_ptr<Choices>& choices) {
  while (!choices->choose(rand() % choices->choices.size())) {} // TODO replace it at some point
}
void AbstractPlayer::initialise(unsigned short player_index) {
  index = player_index;
  left_index  = (index - 1) % Players.size();
  right_index = (index + 1) % Players.size();
  left  = Players[left_index ];
  right = Players[right_index];

  pot = std::make_shared<ChipGroup>();
  drops[0] = std::make_shared<Chip>();
  drops[1] = std::make_shared<Chip>();
  pot->addChip(drops[0]);

  masterBag = std::make_shared<ChipGroup>();
  masterBag->addChip(ChipLibrary::make(CherryBomb, 0));
  masterBag->addChip(ChipLibrary::make(CherryBomb, 0));
  masterBag->addChip(ChipLibrary::make(CherryBomb, 0));
  masterBag->addChip(ChipLibrary::make(CherryBomb, 0));
  masterBag->addChip(ChipLibrary::make(CherryBomb, 1));
  masterBag->addChip(ChipLibrary::make(CherryBomb, 1));
  masterBag->addChip(ChipLibrary::make(CherryBomb, 2));
  masterBag->addChip(ChipLibrary::make(Pumpkin, 0));
  masterBag->addChip(ChipLibrary::make(GardenSpider, 0));
}
