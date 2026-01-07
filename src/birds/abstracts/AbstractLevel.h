#ifndef BIRDSARESWAG_ABSTRACT_LEVEL_H
#define BIRDSARESWAG_ABSTRACT_LEVEL_H

#include "../../abstracts/InputSubscriber.h"
#include "AbstractPlayer.h"
#include <vector>

class AbstractLevel : InputSubscriber {
protected:
  std::vector<Surface> surfaces;
  std::shared_ptr<AbstractPlayer> player;
  sf::Vector2f player_spawn;
  sf::View view;

public:
  void update(float dt);
  void render();
  virtual void load();
  void open();
  void close();
  void unload();
  bool isLoaded = false;
  void Move(sf::Vector2f vector) override;
  void Select(bool down) override;
  void Resize() override;
};

#endif // BIRDSARESWAG_ABSTRACT_LEVEL_H
