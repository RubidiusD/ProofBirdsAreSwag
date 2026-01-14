#include "InputManager.h"
#include "../MathLib.h"
#include "../Settings.h"
#include "MenuManager.h"

std::vector<std::shared_ptr<InputSubscriber>> InputManager::subscribers;
std::shared_ptr<InputSubscriber> InputManager::NothingBurger = std::make_shared<InputSubscriber>();
std::shared_ptr<InputSubscriber> InputManager::CurrentSubscriber = NothingBurger;

void InputManager::subscribe(InputSubscriber* new_subscriber) {
  if (subscribers.empty()) {
    new_subscriber->subscriber_id = 0;
  }
  else {
    new_subscriber->subscriber_id = subscribers.back()->subscriber_id;
  }
  subscribers.emplace_back(new_subscriber);
}

void InputManager::remove(InputSubscriber* subscriber) {
  bool found = false;
  for (int index = 0; index != subscribers.size() - 1; index ++) {
    if (!found) {
      if (subscribers[index]->subscriber_id == subscriber->subscriber_id) {
        found = true;
      }
    }
    if (found) {
      subscribers[index] = subscribers[index + 1];
    }
  }

  subscribers.pop_back();
}

bool InputManager::action_pressed[TOTAL] = {false, false, false, false, false};

void InputManager::manageInput(sf::Event event) {
  if (event.type == sf::Event::Closed) {
    S::Window.close();
    return;
  }

  switch (event.type) {
  case (sf::Event::KeyPressed):
  case (sf::Event::KeyReleased):
    CurrentSubscriber->KeyPressed(event.key.code, event.type == sf::Event::KeyPressed);
    switch (event.key.code) {
    case (sf::Keyboard::W):
    case (sf::Keyboard::Up):
      Up(event.type == sf::Event::KeyPressed); return;
    case (sf::Keyboard::S):
    case (sf::Keyboard::Down):
      Down(event.type == sf::Event::KeyPressed); return;
    case (sf::Keyboard::A):
    case (sf::Keyboard::Left):
      Left(event.type == sf::Event::KeyPressed); return;
    case (sf::Keyboard::D):
    case (sf::Keyboard::Right):
      Right(event.type == sf::Event::KeyPressed); return;
    case (sf::Keyboard::E):
    case (sf::Keyboard::Enter):
    case (sf::Keyboard::Space):
      Select(event.type == sf::Event::KeyPressed); return;
    case (sf::Keyboard::Escape):
      MenuManager::pause(); return;
    default:
      return;
    }
  case (sf::Event::MouseButtonPressed):
  case (sf::Event::MouseButtonReleased):
    if (event.mouseButton.button == sf::Mouse::Left) {
      Select(event.type == sf::Event::MouseButtonPressed);
    } return;
  case (sf::Event::MouseMoved):
    CurrentSubscriber->Point({(float)event.mouseMove.x, (float)event.mouseMove.y});
    CurrentSubscriber->Look(M::norm({(float)event.mouseMove.x - S::ScreenSize.x / 2, (float)event.mouseMove.y - S::ScreenSize.y / 2})); return;
  case (sf::Event::Resized):
    Resize();
  default:
    return;
  }
}

const std::shared_ptr<InputSubscriber>& InputManager::getCurrentSubscriber() {
  for (int index = subscribers.size() - 1; index != -1; index --) {
    if (subscribers[index]->listening_to_inputs) {
      return subscribers[index];
    }
  }
  return NothingBurger;
}

void InputManager::Up(bool down) {
  if (down != action_pressed[UP]) {
    action_pressed[UP] = down;
    CurrentSubscriber->Up(down);
  }
}

void InputManager::Down(bool down) {
  if (down != action_pressed[DOWN]) {
    action_pressed[DOWN] = down;
    CurrentSubscriber->Down(down);
  }
}

void InputManager::Left(bool down) {
  if (down != action_pressed[LEFT]) {
    action_pressed[LEFT] = down;
    CurrentSubscriber->Left(down);
  }
}

void InputManager::Right(bool down) {
  if (down != action_pressed[RIGHT]) {
    action_pressed[RIGHT] = down;
    CurrentSubscriber->Right(down);
  }
}

void InputManager::Select(bool down) {
  if (down != action_pressed[SELECT]) {
    action_pressed[SELECT] = down;
    CurrentSubscriber->Select(down);
  }
}

void InputManager::update(float dt) {
  CurrentSubscriber = getCurrentSubscriber();
  CurrentSubscriber->Move({
      (action_pressed[LEFT] ? -1.0f : 0.0f) + (action_pressed[RIGHT] ? 1.0f : 0.0f),
      (action_pressed[UP] ? -1.0f : 0.0f) + (action_pressed[DOWN] ? 1.0f : 0.0f),
  });
}

void InputManager::Resize() {
  S::ScreenSize = (sf::Vector2f)S::Window.getSize();
  CurrentSubscriber->Resize();
}
