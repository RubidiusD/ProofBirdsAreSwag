#include "InputManager.h"
#include "../Settings.h"

std::vector<std::shared_ptr<InputSubscriber>> InputManager::subscribers;
std::shared_ptr<InputSubscriber> InputManager::NothingBurger = std::make_shared<InputSubscriber>();

void InputManager::subscribe(InputSubscriber* new_subscriber) {
  if (subscribers.empty()) {
    new_subscriber->subscriber_id = 0;
  }
  else {
    new_subscriber->subscriber_id = subscribers.back()->subscriber_id;
  }
  subscribers.emplace_back(new_subscriber);
}

void InputManager::remove(InputSubscriber *subscriber) {
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
  if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
    S::Window.close();
    return;
  }

  switch (event.type) {
  case (sf::Event::KeyPressed):
  case (sf::Event::KeyReleased):
    getCurrentSubscriber()->KeyPressed(event.key.code, event.type == sf::Event::KeyPressed);
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
    default:
      return;
    }
  case (sf::Event::MouseButtonPressed):
  case (sf::Event::MouseButtonReleased):
    if (event.mouseButton.button == sf::Mouse::Left) {
      Select(event.type == sf::Event::MouseButtonPressed);
    } return;
  case (sf::Event::MouseMoved):
    getCurrentSubscriber()->Point({(float)event.mouseMove.x, (float)event.mouseMove.y}); return;
  case (sf::Event::Resized):
    Resize();
  default:
    return;
  }
}

const std::shared_ptr<InputSubscriber>& InputManager::getCurrentSubscriber() {
  for (const std::shared_ptr<InputSubscriber>& subscriber : subscribers) {
    if (subscriber->listening_to_inputs) {
      return subscriber;
    }
  }
  return NothingBurger;
}

void InputManager::Up(bool down) {
  if (down != action_pressed[UP]) {
    action_pressed[UP] = down;
    getCurrentSubscriber()->Up(down);
  }
}

void InputManager::Down(bool down) {
  if (down != action_pressed[DOWN]) {
    action_pressed[DOWN] = down;
    getCurrentSubscriber()->Down(down);
  }
}

void InputManager::Left(bool down) {
  if (down != action_pressed[LEFT]) {
    action_pressed[LEFT] = down;
    getCurrentSubscriber()->Left(down);
  }
}

void InputManager::Right(bool down) {
  if (down != action_pressed[RIGHT]) {
    action_pressed[RIGHT] = down;
    getCurrentSubscriber()->Right(down);
  }
}

void InputManager::Select(bool down) {
  if (down != action_pressed[SELECT]) {
    action_pressed[SELECT] = down;
    getCurrentSubscriber()->Select(down);
  }
}

void InputManager::update(float dt) {
  getCurrentSubscriber()->Move({
      (action_pressed[LEFT] ? -1.0f : 0.0f) + (action_pressed[RIGHT] ? 1.0f : 0.0f),
      (action_pressed[UP] ? -1.0f : 0.0f) + (action_pressed[DOWN] ? 1.0f : 0.0f),
  });
}

void InputManager::Resize() {
  S::Res = (sf::Vector2f)S::Window.getSize();
  getCurrentSubscriber()->Resize();
}
