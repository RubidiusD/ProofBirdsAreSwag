#ifndef BIRDSARESWAG_MENU_MANAGER_H
#define BIRDSARESWAG_MENU_MANAGER_H

#include "../abstracts/AbstractAction.h"
#include "../abstracts/AbstractMenu.h"
#include <SFML/Graphics.hpp>

class MenuManager {
private:
  static std::vector<std::shared_ptr<AbstractMenu>> menus;
  static std::shared_ptr<AbstractMenu> current_menu;

  static sf::Text debug_text;

public:
  static void registerMenu(const std::shared_ptr<AbstractMenu>& new_menu);
  static bool setMenu(unsigned menu_id);
  static bool setMenu(const sf::String& menu_id);
  static bool closeMenu();
  static bool update(float id);
  static void render();

  static bool isLoading;

  // The action for opening a menu (also closes the previous one)
  class OpenMenuAction : public AbstractAction {
  private:
    unsigned index;
    static const float duration;

  public:
    explicit OpenMenuAction(unsigned menu_index);
    void end() override;
  };
  // The action for closing the open menu
  class CloseMenuAction : public AbstractAction {
  private:
    static const float duration;

  public:
    explicit CloseMenuAction();
    void end() override;
  };
};

#endif // BIRDSARESWAG_MENU_MANAGER_H
