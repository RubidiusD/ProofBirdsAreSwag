#ifndef BIRDSARESWAG_PAUSE_MENU_H
#define BIRDSARESWAG_PAUSE_MENU_H

#include "../../abstracts/AbstractMenu.h"
#include "../../abstracts/ScreenElements/TextButton.h"
#include "../../managers/MenuManager.h"
#include "../levels/LevelLibrary.h"

class PauseMenu : public AbstractMenu {
public:
  PauseMenu();
  void load() override;

  class CloseMenuButton : public TextButton {
  public:
    CloseMenuButton(const sf::String& text_, const Neighbours& n, const sf::Vector2f& ratio_) : TextButton(0, text_, n, ratio_) {}
    void Press() override {
      MenuManager::closeMenu();
    }
  };

  class ResetLevelButton : public TextButton {
  public:
    ResetLevelButton(const sf::String& text_, const Neighbours& n, const sf::Vector2f& ratio_) : TextButton(0, text_, n, ratio_) {}
    void Press() override {
      if (LevelLibrary::current_level != nullptr) {
        LevelLibrary::current_level->open();
      }
      MenuManager::closeMenu();
    }
  };

  class LoadMenuButton : public TextButton {
    const sf::String& ID;
  public:
    LoadMenuButton(const sf::String& text_, const Neighbours& n, const sf::Vector2f& ratio_, const sf::String& menu_id) : TextButton(0, text_, n, ratio_), ID(menu_id) {}
    void Press() override {
      printf("Trying to load Menu \n");
      MenuManager::setMenu(ID);
    }
  };
};

#endif // BIRDSARESWAG_PAUSE_MENU_H
