#include "AssetManager.h"

std::vector<std::shared_ptr<AssetManager::TextureAsset>> AssetManager::Textures;
std::vector<std::shared_ptr<AssetManager::FontAsset>> AssetManager::Fonts;
std::vector<std::shared_ptr<AssetManager::SoundAsset>> AssetManager::Sounds;

template <typename type>
bool AssetManager::Insert(std::vector<std::shared_ptr<type>>& array, const std::shared_ptr<type>& item) {
  array.emplace_back(item);
  for (int index = (int)array.size() - 2; index != -1; index --) {
    if (((AssetManager::Asset*)array[index].get())->ID < ((AssetManager::Asset*)item.get())->ID) {
      array[index + 1] = item;
      break;
    } else if (((AssetManager::Asset*)array[index].get())->ID == ((AssetManager::Asset*)item.get())->ID) {
      return false;
    }
    array[index + 1] = array[index];
  }
  return true;
}

bool AssetManager::RegisterTexture(const sf::String& path, unsigned ID) {
  std::shared_ptr<TextureAsset> textureAsset = std::make_shared<TextureAsset>(ID);
  if (Insert<TextureAsset>(Textures, textureAsset)) {
    textureAsset->texture.loadFromFile(path);
    return true;
  }
  return false;
}

bool AssetManager::RegisterFont(const sf::String& path, unsigned ID) {
  std::shared_ptr<FontAsset> fontAsset = std::make_shared<FontAsset>(ID);
  if (Insert<FontAsset>(Fonts, fontAsset)) {
    fontAsset->font.loadFromFile(path);
    return true;
  }
  return false;
}

bool AssetManager::RegisterSound(const sf::String& path, unsigned ID) {
  std::shared_ptr<SoundAsset> soundAsset = std::make_shared<SoundAsset>(ID);
  if (Insert<SoundAsset>(Sounds, soundAsset)) {
    soundAsset->sound.loadFromFile(path);
    return true;
  }
  return false;
}

const sf::Texture& AssetManager::getTexture(unsigned ID) {
  return (BinarySearch<TextureAsset>(Textures, ID)->texture);
}

const sf::Font& AssetManager::getFont(unsigned ID) {
  return (BinarySearch<FontAsset>(Fonts, ID)->font);
}

const sf::SoundBuffer& AssetManager::getSound(unsigned ID) {
  return (BinarySearch<SoundAsset>(Sounds, ID)->sound);
}

template <typename type>
type* AssetManager::BinarySearch(const std::vector<std::shared_ptr<type>>& array, unsigned ID) {
  int lower = -1;
  int upper = array.size();
  while (lower + 1 != upper) {
    int pos = (lower + upper) / 2;
    int id = ((Asset*)array[pos].get())->ID;

    if (id == ID) {
      return array[pos].get();
    }
    else if (id > ID) {
      upper = pos;
    } else {
      lower = pos;
    }
  }
  return nullptr;
}
