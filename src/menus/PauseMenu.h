#ifndef BIRDSARESWAG_PAUSE_MENU_H
#define BIRDSARESWAG_PAUSE_MENU_H

#include "../levels/LevelLibrary.h"
#include "../managers/InputManager.h"
#include "../managers/MenuManager.h"
#include "AbstractMenu.h"
#include "ResultsMenu.h"
#include "ScreenElements/TextButton.h"

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
    //  printf("Trying to load Menu \n");
    MenuManager::setMenu(ID);
  }
};

class OptOutButton : public LoadMenuButton {
public:
  OptOutButton(const sf::String& text_, const Neighbours& n, const Vector2f& ratio_) : LoadMenuButton(text_, n, ratio_, "MAIN") {}
  void Press() override {
    LevelLibrary::current_level->publishProgress(QUIT);
    ResultsMenu::instance->SaveAndCleanseAttempts();
    LoadMenuButton::Press();
    LevelLibrary::setLevel(-1);
  }
};

class ControllerButton : public TextButton {
public:
  ControllerButton(const Neighbours& n, const Vector2f& ratio_) : TextButton(0, "Reset Controller", n, ratio_) {}
  void Press() override {
    //  printf("Resetting ControllerConnected \n");
    InputManager::StartController();
  }
};

class PauseMenu : public AbstractMenu {
public:
  PauseMenu();
  void load() override;
  void Pause(bool down) override;
  void open() override;
  void close() override;
};

#endif // BIRDSARESWAG_PAUSE_MENU_H
