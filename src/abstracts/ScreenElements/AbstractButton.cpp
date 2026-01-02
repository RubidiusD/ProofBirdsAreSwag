#include "AbstractButton.h"
#include "../../managers/Settings.h"

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
