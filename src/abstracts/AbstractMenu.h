#ifndef BIRDSARESWAG_ABSTRACTMENU_H
#define BIRDSARESWAG_ABSTRACTMENU_H

#include "InputSubscriber.h"
#include "ScreenElements/AbstractButton.h"
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <vector>

class AbstractMenu: public InputSubscriber {
protected:
  std::vector<std::shared_ptr<AbstractButton>> buttons;
  std::shared_ptr<AbstractButton> current_button;
  std::vector<std::shared_ptr<sf::Drawable>> static_visuals;
  short current_index = -1;
  unsigned short default_index = 0;

  void selectButton(unsigned short index);
  void addButton(AbstractButton* new_button);
  void addDrawable(sf::Drawable* new_drawable);

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

  void Up(bool down) override;
  void Down(bool down) override;
  void Left(bool down) override;
  void Right(bool down) override;
  void Point(const sf::Vector2f& vector) override;
  void Select(bool down) override;
  void Resize() override;
};

#endif // BIRDSARESWAG_ABSTRACTMENU_H
