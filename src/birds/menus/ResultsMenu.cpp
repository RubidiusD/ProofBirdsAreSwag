#include "ResultsMenu.h"
#include "PauseMenu.h"
#include "../../managers/AssetManager.h"
#include <SFML/Graphics/Text.hpp>

std::vector<Attempt> ResultsMenu::attempts;

void ResultsMenu::load() {
  AbstractMenu::load();
  buttons.emplace_back(new LoadMenuButton("Main Menu", {0, 0, 0, 0}, {0.25, 0.5}, "MAIN"));
}

void ResultsMenu::open() {
  unsigned long long total = attempts.size();
  for (int index = 0; index != total; index ++) {
    sf::Text* text = new sf::Text(std::to_string(index) + ": " + std::to_string(attempts[index].progress) + " in " + std::to_string(attempts[index].duration), AssetManager::getFont(0), 18);
    text->setPosition(S::Res(0.6f, 0.2f + 0.6f * ((float)index / (float)total)));
    addDrawable(text);
  }
  AbstractMenu::open();
}

void ResultsMenu::close() {
  AbstractMenu::close();
  CleanseAttempts();
}

void ResultsMenu::CleanseAttempts() {

}

void ResultsMenu::AddAttempt(float duration, int progress) {

}
