#ifndef BIRDSARESWAG_RECIPE_H
#define BIRDSARESWAG_RECIPE_H

#include "AbstractRecipe.h"

class Recipe : public AbstractRecipe {
public:
  explicit Recipe(const Stats& recipe) : AbstractRecipe(recipe) {}

  unsigned short calculatePosition(unsigned short player_index, const std::shared_ptr<Chip>& chip) override;
};

#endif // BIRDSARESWAG_RECIPE_H
