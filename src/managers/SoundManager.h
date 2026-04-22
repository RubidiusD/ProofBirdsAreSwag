#ifndef BIRDSARESWAG_SOUNDMANAGER_H
#define BIRDSARESWAG_SOUNDMANAGER_H

#include "../Vector2f.hpp"
#include "AssetManager.h"

class SoundManager {
public:
  static void LoadSounds();

  static std::vector<std::shared_ptr<sf::Sound>> sounds;

  static Vector2f listener;

  static void play(unsigned ID);
  static void play(unsigned ID, float volume);
  static void play(unsigned ID, float volume, float variance);
  static void play(unsigned ID, unsigned max_ID, float volume, float variance);
  static void play(const Vector2f& position, unsigned ID);
  static void play(const Vector2f& position, unsigned ID, float volume);
  static void play(const Vector2f& position, unsigned ID, float volume, float variance);
  static void play(const Vector2f& position, unsigned ID, unsigned max_ID, float volume, float variance);

  static void update();
};

#endif // BIRDSARESWAG_SOUNDMANAGER_H
