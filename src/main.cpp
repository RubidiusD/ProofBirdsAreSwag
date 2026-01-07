#include "Settings.h"
#include "birds/Game.h"
#include "birds/levels/LevelLoader.hpp"
#include "birds/menus/MenuLoader.hpp"
#include "managers/ActionManager.h"
#include "managers/InputManager.h"

int main() {
  S::Window.setFramerateLimit(60);
//  S::Window.setMouseCursorVisible(false);
  S::Res = sf::Vector2f(S::Window.getSize());

  MenuLoader::LoadMenus();
  MenuManager::setMenu("SPSH");
  LevelLoader::LoadLevels();
  Game game(S::Window);
  M::initialiseRandomness();

  if (!game.init()) {
    return 0;
  }

  sf::Clock clock;

  while (S::Window.isOpen()) {
    sf::Event event = {};

    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    while (S::Window.pollEvent(event) && S::Window.isOpen()) {
      InputManager::manageInput(event);
    }
    InputManager::update(dt);

    if (S::Window.isOpen()) {
      game.update(dt);
    }

    if (S::Window.isOpen()) {
      game.render();
      S::Window.display();
    }
  }
}