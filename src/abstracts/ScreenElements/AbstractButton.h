#ifndef BIRDSARESWAG_ABSTRACT_BUTTON_H
#define BIRDSARESWAG_ABSTRACT_BUTTON_H

#include <SFML/Graphics/Sprite.hpp>

struct Neighbours { unsigned short u; unsigned short d; unsigned short l; unsigned short r; };

class AbstractButton {
private:
  sf::Sprite sprite;
  bool selected = false;
public:
  void Press();
  void Depress();
  void Select();
  void Deselect();
  void Drag(const sf::Vector2f& vector);

  bool isInside(const sf::Vector2f& vector);
  void Render();
  void Update(float dt);

  // for when navigating a menu with directional inputs
  Neighbours neighbours = {0, 0, 0, 0};

};

#endif // BIRDSARESWAG_ABSTRACT_BUTTON_H
