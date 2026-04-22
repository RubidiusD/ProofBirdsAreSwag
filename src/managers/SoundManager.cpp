#include "SoundManager.h"
#include "../MathLib.h"

std::vector<std::shared_ptr<sf::Sound>> SoundManager::sounds;
Vector2f SoundManager::listener;

void SoundManager::LoadSounds() {
  AssetManager::RegisterSound("Data/audio/Dig_0.wav", 0);
  AssetManager::RegisterSound("Data/audio/Dig_1.wav", 1);
  AssetManager::RegisterSound("Data/audio/Dig_2.wav", 2);
  AssetManager::RegisterSound("Data/audio/Item_32.wav", 5);
  AssetManager::RegisterSound("Data/audio/Item_2.wav", 10);
  AssetManager::RegisterSound("Data/audio/Item_48.wav", 11);
  AssetManager::RegisterSound("Data/audio/Shatter.wav", 12);
  AssetManager::RegisterSound("Data/audio/Item_18.wav", 20);
  AssetManager::RegisterSound("Data/audio/Item_19.wav", 21);
  AssetManager::RegisterSound("Data/audio/Item_39.wav", 22);
  AssetManager::RegisterSound("Data/audio/Item_29.wav", 30); // used
  AssetManager::RegisterSound("Data/audio/Player_Killed.wav", 40);
  AssetManager::RegisterSound("Data/audio/Menu_Open.wav", 50);
  AssetManager::RegisterSound("Data/audio/Menu_Close.wav", 51);
  AssetManager::RegisterSound("Data/audio/Chat.wav", 52);
  AssetManager::RegisterSound("Data/audio/Jump_1.wav", 60);
  AssetManager::RegisterSound("Data/audio/Jump_2.wav", 61);
}

void SoundManager::play(unsigned int ID) {
  sounds.emplace_back(new sf::Sound());
  sounds.back()->setBuffer(AssetManager::getSound(ID));
  sounds.back()->play();
}

void SoundManager::play(unsigned int ID, float volume) {
  play(ID);
  sounds.back()->setVolume(fmaxf(0.0f, volume));
}

void SoundManager::play(unsigned int ID, float volume, float variance) {
  play(ID);
  sounds.back()->setVolume(fmaxf(0.0f, M::Randf(volume - variance, volume + variance)));
  sounds.back()->setPitch(fmaxf(0.0f, M::Randf(1.0f - variance, 1.0f + variance)));
}

void SoundManager::play(unsigned int ID, unsigned int max_ID, float volume, float variance) {
  play(M::Rand(ID, max_ID), volume, variance);
}

void SoundManager::play(const Vector2f &position, unsigned int ID) {
  play(ID);
  sounds.back()->setPosition((position - listener) / 4.0f);
}

void SoundManager::play(const Vector2f &position, unsigned int ID, float volume) {
  play(ID, volume);
  sounds.back()->setPosition((position - listener) / 4.0f);
}

void SoundManager::play(const Vector2f &position, unsigned int ID, float volume, float variance) {
  play(ID, volume, variance);
  sounds.back()->setPosition((position - listener) / 4.0f);
}

void SoundManager::play(const Vector2f &position, unsigned int ID, unsigned int max_ID, float volume, float variance) {
  play(ID, max_ID, volume, variance);
  sounds.back()->setPosition((position - listener) / 4.0f);
}

void SoundManager::update() {
  for (int a = 0; a != sounds.size(); a ++) {
    if (sounds[a]->getStatus() != sf::SoundSource::Status::Playing) {
      for (int b = a; b != sounds.size() - 1; b ++) {
        sounds[b] = sounds[b + 1];
      }
      sounds.pop_back();
      a --;
    }
  }
}
