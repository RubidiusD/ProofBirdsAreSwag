#ifndef BIRDSARESWAG_BILLBOARD_H
#define BIRDSARESWAG_BILLBOARD_H

#include "../AbstractLevelElement.h"

class Billboard : public AbstractLevelElement {
public:
  Billboard(const Vector2f& pos, float rotation, const sf::Texture& texture) : AbstractLevelElement(pos) {
    sprite.setOrigin((float) texture.getSize().x / 2, (float) texture.getSize().y / 2);
    sprite.setTexture(texture);
    sprite.setRotation(rotation);
  }
};

#endif // BIRDSARESWAG_BILLBOARD_H
