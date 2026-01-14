#ifndef BIRDSARESWAG_ASSET_MANAGER_H
#define BIRDSARESWAG_ASSET_MANAGER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class AssetManager {
private:
  struct Asset {
    unsigned ID;
    Asset(unsigned ID_) { ID = ID_; }
  };
  struct TextureAsset : Asset {
    sf::Texture texture;
    TextureAsset(unsigned ID_) : Asset(ID_) {}
  };
  struct FontAsset : Asset {
    sf::Font font;
    FontAsset(unsigned ID_) : Asset(ID_) {}
  };
  struct SoundAsset : Asset {
    sf::SoundBuffer sound;
    SoundAsset(unsigned ID_) : Asset(ID_) {}
  };
  static std::vector<std::shared_ptr<TextureAsset>> Textures;
  static std::vector<std::shared_ptr<FontAsset>> Fonts;
  static std::vector<std::shared_ptr<SoundAsset>> Sounds;

  template<typename type>
  static bool Insert(std::vector<std::shared_ptr<type>>& array, const std::shared_ptr<type>& item);
  template<typename type>
  static type* BinarySearch(const std::vector<std::shared_ptr<type>>& array, unsigned ID);
public:
  static bool RegisterTexture(const sf::String& path, unsigned ID);
  static bool RegisterFont   (const sf::String& path, unsigned ID);
  static bool RegisterSound  (const sf::String& path, unsigned ID);
  static const sf::Texture& getTexture(unsigned ID);
  static const sf::Font& getFont(unsigned ID);
  static const sf::SoundBuffer& getSound(unsigned ID);
};

#endif // BIRDSARESWAG_ASSET_MANAGER_H
