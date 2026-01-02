#include "Game.h"
#include "managers/ActionManager.h"
#include "managers/InputManager.h"
#include "managers/Settings.h"

int main() {
  S::Window.setFramerateLimit(60);
  S::Window.setMouseCursorVisible(false);
  S::Res = sf::Vector2f(S::Window.getSize());

  Game game(S::Window);

  if (!game.init()) {
    return 0;
  }

  sf::Clock clock;

  while (S::Window.isOpen()) {
    sf::Event event = {};

    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    while (S::Window.pollEvent(event) && S::Window.isOpen()) {
      InputManager::manageInputs(event);
    }

    if (S::Window.isOpen()) {
      game.update(dt);
    }

    if (S::Window.isOpen()) {
      game.render();
      S::Window.display();
    }
  }
}