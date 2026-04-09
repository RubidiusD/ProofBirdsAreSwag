#ifndef BIRDSARESWAG_ABSTRACT_BUTTON_H
#define BIRDSARESWAG_ABSTRACT_BUTTON_H

#include "../../../Settings.h"
#include "../../../Vector2f.hpp"
#include <SFML/Graphics/Sprite.hpp>

struct Neighbours { unsigned short u; unsigned short d; unsigned short l; unsigned short r; };

class AbstractButton {
protected:
  sf::Sprite sprite;
  bool selected = false;
  Vector2f ratio;
public:
  virtual void Press() {}
  virtual void Depress() {}
  virtual void Select() { selected = true; }
  virtual void Deselect() { selected = false; }
  virtual void Drag(const Vector2f& vector) { }

  bool isInside(const Vector2f& vector) {
    sf::Rect<float> rect = sprite.getGlobalBounds();
    return (
        vector.x < rect.left + rect.width &&
        vector.y < rect.top + rect.height  &&
        vector.x > rect.left &&
        vector.y > rect.top
    );
  }

  virtual void Render() { S::Window.draw(sprite); }
  void Update(float dt) { }

  // for when navigating a menu with directional inputs
  Neighbours neighbours = {0, 0, 0, 0};

  AbstractButton(const Neighbours& n, const sf::Texture& texture) {
    neighbours = n;
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
  }

  AbstractButton(const Neighbours& n, const sf::Texture& texture, const Vector2f& ratio_) : AbstractButton(n, texture) {
    ratio = ratio_;
    sprite.setPosition(S::Res * ratio);
  }
};

#endif // BIRDSARESWAG_ABSTRACT_BUTTON_H
