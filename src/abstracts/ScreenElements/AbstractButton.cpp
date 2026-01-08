#include "AbstractButton.h"
#include "../../MathLib.h"
#include "../../Settings.h"

void AbstractButton::Press() {}
void AbstractButton::Depress() {}
void AbstractButton::Select() {
  selected = true;
}
void AbstractButton::Deselect() {
  selected = false;
}
void AbstractButton::Drag(const sf::Vector2f& vector) {}
void AbstractButton::Update(float dt) {}
void AbstractButton::Render() {
  S::Window.draw(sprite);
}
bool AbstractButton::isInside(const sf::Vector2f& vector) {
  sf::Rect<float> rect = sprite.getGlobalBounds();
  return (
      vector.x < rect.left + rect.width &&
      vector.y < rect.top + rect.height  &&
      vector.x > rect.left &&
      vector.y > rect.top
  );
}
AbstractButton::AbstractButton(const Neighbours &n, const sf::Texture &texture) {
  neighbours = n;
  sprite.setTexture(texture);
  sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

AbstractButton::AbstractButton(const Neighbours &n, const sf::Texture &texture, const sf::Vector2f &ratio_) : AbstractButton(n, texture) {
  ratio = ratio_;
  sprite.setPosition(M::scale(S::Res, ratio));
}
