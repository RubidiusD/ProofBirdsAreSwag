#ifndef BIRDSARESWAG_ABSTRACT_LEVEL_H
#define BIRDSARESWAG_ABSTRACT_LEVEL_H

#include "../LevelElements/players/AbstractPlayer.h"
#include "../LevelElements/projectiles/Egg.h"
#include "../LevelElements/util/PlayerListener.h"

class AbstractLevel : InputSubscriber {
protected:
  std::vector<Surface> surfaces;
  std::shared_ptr<AbstractPlayer> player;
  std::vector<std::shared_ptr<AbstractLevelElement>> elements;
  sf::View view;
  std::vector<std::shared_ptr<AbstractWind>> winds;
  std::vector<PlayerListener*> listeners;

  float particle_rate = 0.1f;
  void windParticles(float dt);

public:
  void update(float dt);
  virtual void render();
  virtual void load();
  virtual void open();
  virtual void close();
  void unload();
  bool isLoaded = false;
  void Move(const Vector2f& vector) override;
  void Select(bool down) override;
  void Look(const Vector2f& vector) override;
  void Pause(bool down) override;
  void Resize() override;
  void addElement(AbstractLevelElement* element);
  void addListener(PlayerListener* element);
  void spawnParticle(const Vector2f& position, const Vector2f& velocity);
  void spawnParticle(unsigned number, const Vector2f& position, const Vector2f& direction);
  void removeListener(PlayerListener& listener);

  Vector2f windAt(const Vector2f& point) const;
  virtual void hurtPlayer(const Vector2f& source);
  std::shared_ptr<AbstractPlayer> getPlayer();
};

#endif // BIRDSARESWAG_ABSTRACT_LEVEL_H
