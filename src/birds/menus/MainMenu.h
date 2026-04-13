#ifndef BIRDSARESWAG_MAIN_MENU_H
#define BIRDSARESWAG_MAIN_MENU_H

#include "../../Settings.h"
#include "../../managers/AssetManager.h"
#include "../../managers/MenuManager.h"
#include "../levels/LevelLibrary.h"
#include "AbstractMenu.h"
#include "ScreenElements/DragButton.h"

class MainMenu : public AbstractMenu {
public:
  MainMenu();
  void load() override;

  class CloseGameButton : public TextButton {
  public:
    CloseGameButton(const Neighbours& n, const Vector2f& ratio_) : TextButton(0, "Close", n, ratio_) {}
    void Press() override {S::Window.close();}
  };

  class LoadLevelButton : public TextButton {
    unsigned index;
  public:
    LoadLevelButton(const sf::String& text_, const Neighbours& n, const Vector2f& ratio_, unsigned index_) : TextButton(0, text_, n, ratio_) {index = index_;}
    void Press() override {
      MenuManager::closeMenu();
      LevelLibrary::setLevel(index);
    }
  };

  class PlayerIndexButton : public DragButton {
  public:
    PlayerIndexButton(const Neighbours& n, const Vector2f& ratio_) : DragButton(0, "Player Index: ", 0.0f, 32.0f, "", n, ratio_) { S::player_index = (unsigned)value; };
    void Depress() override { S::player_index = (unsigned)value; }
  };
};

#endif // BIRDSARESWAG_MAIN_MENU_H
