#include "MenuManager.h"
#include "ActionManager.h"
#include "AssetManager.h"
#include "Settings.h"

std::vector<std::shared_ptr<AbstractMenu>> MenuManager::menus = std::vector<std::shared_ptr<AbstractMenu>>();
std::shared_ptr<AbstractMenu> MenuManager::current_menu = nullptr;
sf::Text MenuManager::debug_text = sf::Text();

void MenuManager::registerMenu(const std::shared_ptr<AbstractMenu>& new_menu) {
  menus.emplace_back(new_menu);
  for (int index = (int)menus.size() - 2; index != -1; index --) {
    if (menus[index]->ID < new_menu->ID) {
      menus[index + 1] = new_menu;
      break;
    }
    menus[index + 1] = menus[index];
  }
}

bool MenuManager::setMenu(unsigned menu_id) {
  short lowest_index = -1;
  auto highest_index = (short)menus.size();
  while (highest_index != 1 + lowest_index) {
    short checking_index = (lowest_index + highest_index) / 2; // NOLINT(*-narrowing-conversions)

    if (menus[checking_index]->ID == menu_id) {
      ActionManager::addToBot(std::make_shared<OpenMenuAction>(checking_index));
      return true;
    }
    else if (menus[checking_index]->ID > menu_id) {
      highest_index = checking_index;
    }
    else {
      lowest_index = checking_index;
    }
  }
  return false;
}

bool MenuManager::setMenu(const sf::String& menu_id) {
  return setMenu(AbstractMenu::makeID(menu_id));
}

void MenuManager::update(float dt) {
  if (current_menu != nullptr) {
    current_menu->update(dt);
  }
}

void MenuManager::render() {
  if (current_menu != nullptr) {
    current_menu->render();
    S::Window.draw(debug_text);
  }
}

const float MenuManager::OpenMenuAction::duration = 0.1f;

void MenuManager::OpenMenuAction::start() {
  isLoading = true;
}

void MenuManager::OpenMenuAction::update(float dt) {
  tick(dt);
}

void MenuManager::OpenMenuAction::end() {
  isLoading = false;
  if (current_menu != nullptr) {
    current_menu->close();
  }
  current_menu = menus[index];
  if (!current_menu->isLoaded) {
    current_menu->load();
  }
  current_menu->open();
  debug_text.setFont(AssetManager::getFont(0));
  debug_text.setFillColor(sf::Color::White);
  debug_text.setString(std::to_string(current_menu->ID));
}

bool MenuManager::isLoading = false;
