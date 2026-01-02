#ifndef BIRDSARESWAG_ABSTRACTMENU_H
#define BIRDSARESWAG_ABSTRACTMENU_H

#include "ScreenElements/AbstractButton.h"
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <vector>

enum InputAction {
  Up,
  Down,
  Left,
  Right,
  Select,
  InputActionTotal
};

enum MouseInputAction {
  Move,
  Press,
  Depress,
  MouseInputActionTotal
};

class AbstractMenu {
private:
  std::vector<std::shared_ptr<AbstractButton>> buttons;
  std::shared_ptr<AbstractButton> current_button;
  short current_index = -1;
  unsigned short default_index = 0;

  void selectButton(unsigned short index);

public:

  static unsigned makeID(const sf::String& menu_id);

  explicit AbstractMenu(unsigned id) {
    ID = id;
  }

  explicit AbstractMenu(const sf::String& id) : AbstractMenu(makeID(id)) {}


  unsigned ID = 0;
  bool isLoaded = false;

  virtual void load();
  virtual void unload();
  virtual void open();
  virtual void close();
  virtual void update(float dt);
  virtual void render();
  virtual void input(InputAction action, bool down);
  virtual void mouseInput(MouseInputAction action, sf::Vector2f vector);
  virtual bool keyPressed(sf::Keyboard::Key key, bool down);
};

#endif // BIRDSARESWAG_ABSTRACTMENU_H
