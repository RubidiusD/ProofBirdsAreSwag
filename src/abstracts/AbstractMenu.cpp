#include "AbstractMenu.h"
#include "../managers/Settings.h"

void AbstractMenu::load() {
  isLoaded = true;
}

void AbstractMenu::unload() {
  isLoaded = false;
  current_button = nullptr;
  current_index = -1;
  buttons.clear();
  static_visuals.clear();
}

void AbstractMenu::open() {

}

void AbstractMenu::close() {

}

bool AbstractMenu::keyPressed(sf::Keyboard::Key key, bool down) {
  return false;
}

void AbstractMenu::update(float dt) {
  for (const std::shared_ptr<AbstractButton>& button : buttons) {
    button->Update(dt);
  }
}

void AbstractMenu::render() {
  for (const std::shared_ptr<sf::Drawable>& drawable : static_visuals) {
    S::Window.draw(*drawable);
  }
  for (const std::shared_ptr<AbstractButton>& button : buttons) {
    button->Render();
  }
}

void AbstractMenu::input(InputAction action, bool down) {
  // if a button is hovered
  if (current_button != nullptr) {
    if (down && action != Select) {
      S::CursorMode = false;
      switch (action) {
      case (Up): selectButton(current_button->neighbours.u); break;
      case (Down): selectButton(current_button->neighbours.d); break;
      case (Left): selectButton(current_button->neighbours.l); break;
      case (Right): selectButton(current_button->neighbours.r); break;
      default: break;
      }
    }
    else if (down) {
      current_button->Press();
    }
    else {
      current_button->Depress();
    }
  }
  else if (action != Select) {
    selectButton(default_index);
  }
}

void AbstractMenu::mouseInput(MouseInputAction action, sf::Vector2f vector) {
  if (current_button != nullptr) {
    switch (action) {
    case (Press): current_button->Press(); break;
    case (Depress): current_button->Depress(); break;
    case (Move):
      if (S::CursorDown) {
        current_button->Drag(vector);
      }
      else if (!current_button->isInside(vector)) {
        current_button->Deselect();
        current_button = nullptr;
        current_index = -1;
      }
      break;
    }
  }

  if (current_button == nullptr) {
    for (unsigned short index = 0; index != buttons.size(); index ++) {
      if (buttons[index]->isInside(vector)) {
        selectButton(index);
        break;
      }
    }
  }
}

unsigned AbstractMenu::makeID(const sf::String &menu_id) {
  unsigned int_id = 0;
  int_id += (unsigned) menu_id[0];
  int_id *= 256;
  int_id += (unsigned) menu_id[1];
  int_id *= 256;
  int_id += (unsigned) menu_id[2];
  int_id *= 256;
  int_id += (unsigned) menu_id[3];
  return int_id;
}

void AbstractMenu::selectButton(unsigned short index) {
  if (index < buttons.size() && index != current_index) {
    if (current_button != nullptr) {
      current_button->Deselect();
    }
    current_button = buttons[index];
    current_button->Select();
    current_index = (short signed) index;
  }
}

void AbstractMenu::addButton(AbstractButton* new_button) {
  buttons.emplace_back(new_button);
}

void AbstractMenu::addDrawable(sf::Drawable* new_drawable) {
  static_visuals.emplace_back(new_drawable);
}
