#ifndef BIRDSARESWAG_PAUSE_MENU_H
#define BIRDSARESWAG_PAUSE_MENU_H

#include "../../abstracts/AbstractMenu.h"
#include "../../abstracts/ScreenElements/TextButton.h"
#include "../../managers/MenuManager.h"
#include "../levels/LevelLibrary.h"

class CloseMenuButton : public TextButton {
public:
  CloseMenuButton(const sf::String& text_, const Neighbours& n, const Vector2f& ratio_) : TextButton(0, text_, n, ratio_) {}
  void Press() override {
    MenuManager::closeMenu();
    LevelLibrary::resumeLevel(false);
  }
};

class ResetLevelButton : public TextButton {
public:
  ResetLevelButton(const sf::String& text_, const Neighbours& n, const Vector2f& ratio_) : TextButton(0, text_, n, ratio_) {}
  void Press() override {
    MenuManager::closeMenu();
    LevelLibrary::resumeLevel(true);
  }
};

class LoadMenuButton : public TextButton {
  unsigned ID;
public:
  LoadMenuButton(const sf::String& text_, const Neighbours& n, const Vector2f& ratio_, const sf::String& menu_id) : TextButton(0, text_, n, ratio_) {ID = AbstractMenu::makeID(menu_id);}
  void Press() override {
    printf("Trying to load Menu \n");
    MenuManager::setMenu(ID);
  }
};

class OptOutButton : public LoadMenuButton {
public:
  OptOutButton(const sf::String& text_, const Neighbours& n, const Vector2f& ratio_) : LoadMenuButton(text_, n, ratio_, "MAIN") {}
  void Press() override {
    LevelLibrary::current_level->publishProgress(QUIT);
    LoadMenuButton::Press();
  }
};

class PauseMenu : public AbstractMenu {
public:
  PauseMenu();
  void load() override;
  void Pause(bool down) override;
};

#endif // BIRDSARESWAG_PAUSE_MENU_H
