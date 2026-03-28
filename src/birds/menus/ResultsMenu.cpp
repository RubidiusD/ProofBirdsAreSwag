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
  printf("Trying to open that thang \n");
  unsigned long long total = attempts.size();
  for (int index = 0; index != total; index ++) {
    sf::Text* text = new sf::Text(std::to_string(index + 1) + ": " + std::to_string(attempts[index].progress) + " - " + attempts[index].look_nice(), AssetManager::getFont(0), 18);
    printf("Going for it with %u: %u \n", index + 1, attempts[index].progress);
    text->setPosition(S::Res(0.6f, 0.2f + 0.6f * ((float)index / (float)total)));
    text->setFillColor({150, 255, 185});
    addDrawable(text);
  }
  printf("Done lol \n");
  AbstractMenu::open();
  printf("Opened it :) \n");
  LevelLibrary::setLevel(-1);
  printf("Closed it :) \n");
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

void ResultsMenu::AddChapter(unsigned int p, float d, unsigned int h, float s, unsigned int j, unsigned int c, unsigned int b, unsigned int l, ProgressType t) {
  if (attempts.empty() || attempts.back().type != UNFINISHED) {
    attempts.emplace_back();
    attempts.back().AddChapter(p, d, h, s, j, c, b, l, t);
  }
  else {
    attempts.back().AddChapter(p, d, h, s, j, c, b, l, t);
  }
}

void ResultsMenu::AddChapter(const Chapter& new_attempt) {
  if (attempts.empty() || attempts.back().type != UNFINISHED) {
    attempts.emplace_back();
    attempts.back().AddChapter(new_attempt);
  }
  else {
    attempts.back().AddChapter(new_attempt);
  }
}
