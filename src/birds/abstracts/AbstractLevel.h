#ifndef BIRDSARESWAG_ABSTRACT_LEVEL_H
#define BIRDSARESWAG_ABSTRACT_LEVEL_H

#include "../../abstracts/InputSubscriber.h"
#include "AbstractPlayer.h"
#include "AbstractWind.h"
#include <vector>

class AbstractLevel : InputSubscriber {
protected:
  std::vector<Surface> surfaces;
  std::shared_ptr<AbstractPlayer> player;
  std::vector<std::shared_ptr<AbstractLevelElement>> elements;
  sf::Vector2f player_spawn;
  sf::View view;
  std::vector<std::shared_ptr<AbstractWind>> winds;

public:
  void update(float dt);
  virtual void render();
  virtual void load();
  void open();
  void close();
  void unload();
  bool isLoaded = false;
  void Move(const sf::Vector2f& vector) override;
  void Select(bool down) override;
  void Look(const sf::Vector2f &vector) override;
  void Pause(bool down) override;
  void Resize() override;
  void addElement(AbstractLevelElement* element);
};

#endif // BIRDSARESWAG_ABSTRACT_LEVEL_H
