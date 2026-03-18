#include "ResultsMenu.h"
#include "PauseMenu.h"
#include "../../managers/AssetManager.h"
#include <SFML/Graphics/Text.hpp>

std::shared_ptr<ResultsMenu> ResultsMenu::instance;
void ResultsMenu::Register() {
  instance = std::make_shared<ResultsMenu>();
  MenuManager::registerMenu(instance);
}

void ResultsMenu::load() {
  AbstractMenu::load();
  buttons.emplace_back(new LoadMenuButton("Main Menu", {0, 0, 0, 0}, {0.25, 0.5}, "MAIN"));
}

void ResultsMenu::open() {
  unsigned long long total = attempts.size();
  for (int index = 0; index != total; index ++) {
    sf::Text* text = new sf::Text(std::to_string(index + 1) + ": " + std::to_string(attempts[index].progress) + " - " + attempts[index].look_nice(), AssetManager::getFont(0), 18);
    text->setPosition(S::Res(0.6f, 0.2f + 0.6f * ((float)index / (float)total)));
    text->setFillColor({150, 255, 185});
    addDrawable(text);
  }
  AbstractMenu::open();
  LevelLibrary::setLevel(-1);
}

void ResultsMenu::close() {
  AbstractMenu::close();
  CleanseAttempts();
}

void ResultsMenu::CleanseAttempts() {
  for (int index = (int)attempts.size() - 1; index != -1; index --) {
    attempts.pop_back();
    static_visuals.pop_back();
  }
}

void ResultsMenu::AddAttempt(float duration, unsigned progress) {
  attempts.emplace_back(duration, progress);
}
