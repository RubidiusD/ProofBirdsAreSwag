#ifndef BIRDSARESWAG_MAIN_MENU_H
#define BIRDSARESWAG_MAIN_MENU_H

#include "../../Settings.h"
#include "../../abstracts/AbstractMenu.h"
#include "../../abstracts/ScreenElements/TextButton.h"
#include "../../managers/AssetManager.h"
#include "../../managers/MenuManager.h"
#include "../levels/LevelLibrary.h"

class MainMenu : public AbstractMenu {
public:
  MainMenu();
  void load() override;

  class CloseGameButton : public TextButton {
  public:
    CloseGameButton(const Neighbours& n, const sf::Vector2f& ratio_) : TextButton(0, "Close", n, ratio_) {}
    void Press() override {S::Window.close();}
  };

  class LoadLevelButton : public TextButton {
    unsigned index;
  public:
    LoadLevelButton(const sf::String& text_, const Neighbours& n, const sf::Vector2f& ratio_, unsigned index_) : TextButton(0, text_, n, ratio_) {index = index_;}
    void Press() override {
      MenuManager::closeMenu();
      LevelLibrary::setLevel(index);
    }
  };
};

#endif // BIRDSARESWAG_MAIN_MENU_H
