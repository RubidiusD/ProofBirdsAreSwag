#include "TextButton.h"
#include "../../Settings.h"
#include "../../managers/AssetManager.h"

TextButton::TextButton(unsigned int font, const sf::String& text_, const Neighbours& n, const sf::Vector2f& ratio_)
    : AbstractButton(n, AssetManager::getTexture(1), ratio_) {
  text.setString(text_);
  text.setFont(AssetManager::getFont(font));
  text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
}

TextButton::TextButton(unsigned int font, const sf::String &text_, const Neighbours &n)
    : TextButton(font, text_, n, {}) {

}

void TextButton::Reposition() {
  AbstractButton::Reposition();
  text.setPosition(sprite.getPosition());
}
void TextButton::Render() {
  AbstractButton::Render();
  S::Window.draw(text);
}
