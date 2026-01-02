#include "Recipe.h"
#include "../chips/ChipLibrary.h"
#include "AbstractPlayer.h"

unsigned short Recipe::calculatePosition(unsigned short player_index, const std::shared_ptr<Chip>& chip) {
  AbstractRecipe::calculatePosition(player_index, chip);
  ChipLibrary::recipes[Players[player_index]->pot->lastChip()->colour]->modifyNext(player_index, Players[player_index]->pot->lastChip(), chip);
  return chip->position;
}
