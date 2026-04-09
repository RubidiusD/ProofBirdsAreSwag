#ifndef BIRDSARESWAG_TEXT_BUTTON_H
#define BIRDSARESWAG_TEXT_BUTTON_H

#include "../../../managers/AssetManager.h"
#include "AbstractButton.h"
#include <SFML/Graphics/Text.hpp>

class TextButton : public AbstractButton {
protected:
  sf::Text text;
public:
  TextButton(unsigned font, const sf::String& text_, const Neighbours& n, const Vector2f& ratio_) : AbstractButton(n, AssetManager::getTexture(1), ratio_) {
    text.setString(text_);
    text.setFont(AssetManager::getFont(font));
    text.setCharacterSize(24);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height * 3 / 4);
    text.setPosition(sprite.getPosition());
  }

  void Render() override {
    AbstractButton::Render();
    S::Window.draw(text);
  }
  void Select() override { text.setFillColor(sf::Color::Yellow); }
  void Deselect() override { text.setFillColor(sf::Color::White); }
};

#endif // BIRDSARESWAG_TEXT_BUTTON_H
