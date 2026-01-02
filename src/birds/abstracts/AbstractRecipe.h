#ifndef BIRDSARESWAG_ABSTRACTRECIPE_H
#define BIRDSARESWAG_ABSTRACTRECIPE_H

#include "../../abstracts/AbstractAction.h"
#include "../chips/ChipGroup.h"

class AbstractRecipe {
public:
  struct Price {unsigned short v = 0; unsigned short c = 0; bool exists() const {return v != 0;}};
  struct Stats {const Colour c; const std::string id; const Price p[3]; const S::DLC r;};

  Colour colour = Null;
  std::string recipeID;
  Price prices[3] = {};
  S::DLC required = S::Vanilla;

  static void addToBot(const std::shared_ptr<AbstractAction>& action);
  static void addToTop(const std::shared_ptr<AbstractAction>& action);

  explicit AbstractRecipe(const Stats& stats) {
    colour = stats.c;
    recipeID = stats.id;
    for (int index = 0; index != 3; index ++)
      prices[index] = stats.p[index];
    required = stats.r;
  }

  std::shared_ptr<Chip> make(unsigned short index) const;
  std::vector<std::shared_ptr<Chip>> makeAll() const;

  bool owns() const;

  virtual bool canUpgrade(unsigned short tier) const;
  void upgrade(const std::shared_ptr<Chip>& chip) const;

  virtual bool canUse() const {return owns();};
  virtual void obtain(unsigned short player_index, int tier);
  virtual void purchase(unsigned short player_index, int tier);
  virtual unsigned short calculatePosition(unsigned short player_index, const std::shared_ptr<Chip>& chip);
  virtual void endOfRound() {};
  virtual void endOfRound(unsigned short player_index) {};
  virtual void onPlace(unsigned short player_index, const std::shared_ptr<Chip>& chip) {};
  virtual void prePlace(unsigned short player_index, const std::shared_ptr<Chip>& chip) {};
  virtual unsigned short modifyNext(unsigned short player_index, const std::shared_ptr<Chip>& this_chip, const std::shared_ptr<Chip>& chip) { return 0; };
  virtual unsigned short modifySelf(unsigned short player_index, const std::shared_ptr<Chip>& chip) { return 0; };
};

#endif // BIRDSARESWAG_ABSTRACTRECIPE_H
