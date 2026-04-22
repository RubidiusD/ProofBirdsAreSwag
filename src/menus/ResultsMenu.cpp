#include "ResultsMenu.h"
#include "../LevelElements/enemies/Bird2.h"
#include "../LevelElements/enemies/Bird3.h"
#include "../LevelElements/enemies/Bird4.h"
#include "PauseMenu.h"
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include <iostream>

std::shared_ptr<ResultsMenu> ResultsMenu::instance;
std::shared_ptr<AbstractBird> ResultsMenu::bird;
std::vector<std::shared_ptr<AbstractBird>> ResultsMenu::birds;

void ResultsMenu::Register() {
  instance = std::make_shared<ResultsMenu>();
  MenuManager::registerMenu(instance);
  birds.emplace_back(new Bird2({0, 0}));
  birds.emplace_back(new Bird3({0, 0}));
  birds.emplace_back(new Bird4({0, 0}));
}

void ResultsMenu::load() {
  AbstractMenu::load();
  buttons.emplace_back(new LoadMenuButton("Main Menu", {0, 0, 0, 0}, {0.25, 0.5}, "MAIN"));
}

void ResultsMenu::open() {
  while (true) {
    if (attempts.back().duration < 1.0f)
      attempts.pop_back();
    else
      break;
  }

  unsigned long long total = attempts.size();
  for (int index = 0; index != total; index ++) {
    sf::Text* text = new sf::Text(std::to_string(index + 1) + ": " + std::to_string(attempts[index].progress) + " - " + attempts[index].look_nice(), AssetManager::getFont(0), 18);
    //  printf("Going for it with %u: %u \n", index + 1, attempts[index].progress);
    text->setPosition(S::Res(0.6f, 0.2f + 0.6f * ((float)index / (float)total)));
    text->setFillColor({150, 255, 185});
    addDrawable(text);
  }
  AbstractMenu::open();
  LevelLibrary::setLevel(-1);
}

void ResultsMenu::close() {
  AbstractMenu::close();
  SaveAndCleanseAttempts();
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

void ResultsMenu::SaveAndCleanseAttempts() {
  std::ofstream file("RecordOf" + std::to_string(S::player_index) + bird->name + ".txt");

  file << "Birds Remaining: " << birds.size() << std::endl;

  for (const auto& run : attempts) {
    file << " %% Attempt: " << run.duration << std::endl;
    file << "Time of first egg: " << run.first_egg << std::endl;
    file << "Time of second egg: " << run.second_egg << std::endl;
    for (const auto& chapter : run.chapters) {
      file << "    Chapter: " << chapter.progress << std::endl;
      file << "Type: " << chapter.type << std::endl;
      file << "Duration: " << chapter.duration << std::endl;
      file << "Times Hit: " << chapter.times_hit << std::endl;
      file << "Time Spent Counter Steering: " << chapter.time_spent_counter_steering << std::endl;
      file << "Times Jumped: " << chapter.times_jumped << std::endl;
      file << "Times Coyoted: " << chapter.times_coyoted << std::endl;
      file << "Times Bounced: " << chapter.times_bounced << std::endl;
      file << "Times Stuck: " << chapter.times_stuck << std::endl;
    }
  }

  file.close();

  // Cleansing Them Attempts
  attempts.clear();
  static_visuals.clear();
}
