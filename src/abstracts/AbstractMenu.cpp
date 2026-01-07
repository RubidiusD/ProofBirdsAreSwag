#include "AbstractMenu.h"
#include "../Settings.h"
#include "../managers/InputManager.h"

void AbstractMenu::load() {
  isLoaded = true;
  InputManager::subscribe(this);
}

void AbstractMenu::unload() {
  isLoaded = false;
  current_button = nullptr;
  current_index = -1;
  buttons.clear();
  static_visuals.clear();
  InputManager::remove(this);
}

void AbstractMenu::open() {
  for (const std::shared_ptr<AbstractButton>& button : buttons) {
    button->Reposition();
  }
  listening_to_inputs = true;
}

void AbstractMenu::close() {
  listening_to_inputs = false;
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

void AbstractMenu::Up(bool down) {
  S::CursorMode = false;
  if (down) {
    if (current_button == nullptr) selectButton(default_index);
    else selectButton(current_button->neighbours.u);
  }
}

void AbstractMenu::Down(bool down) {
  S::CursorMode = false;
  if (down) {
    if (current_button == nullptr) selectButton(default_index);
    else selectButton(current_button->neighbours.d);
  }
}

void AbstractMenu::Left(bool down) {
  S::CursorMode = false;
  if (down) {
    if (current_button == nullptr) selectButton(default_index);
    else selectButton(current_button->neighbours.l);
  }
}

void AbstractMenu::Right(bool down) {
  S::CursorMode = false;
  if (down) {
    if (current_button == nullptr) selectButton(default_index);
    else selectButton(current_button->neighbours.r);
  }
}

void AbstractMenu::Point(sf::Vector2f vector) {
  if (current_button != nullptr) {
    if (S::CursorDown) {
      current_button->Drag(vector);
    }
    else if (!current_button->isInside(vector)) {
      current_button->Deselect();
      current_button = nullptr;
      current_index = -1;
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

void AbstractMenu::Select(bool down) {
  if (current_button != nullptr) {
    if (down) {
      current_button->Press();
    } else {
      current_button->Depress();
    }
  }
}

void AbstractMenu::Resize() {
  for (const std::shared_ptr<AbstractButton>& button : buttons) {
    button->Reposition();
  }
}
