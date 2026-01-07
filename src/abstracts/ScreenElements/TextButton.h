#ifndef BIRDSARESWAG_TEXT_BUTTON_H
#define BIRDSARESWAG_TEXT_BUTTON_H

#include "AbstractButton.h"
#include <SFML/Graphics/Text.hpp>

class TextButton : public AbstractButton {
protected:
  sf::Text text;
public:
  TextButton(unsigned font, const sf::String& text_, const Neighbours& n);
  TextButton(unsigned font, const sf::String& text_, const Neighbours& n, const sf::Vector2f& ratio_);

  void Reposition() override;
  void Render() override;
};

#endif // BIRDSARESWAG_TEXT_BUTTON_H
