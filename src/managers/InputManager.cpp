#include "InputManager.h"
#include "../../../QuacksOfQuedlinburg/src/MathLib.h"
#include "../Settings.h"
#include "MenuManager.h"

std::vector<std::shared_ptr<InputSubscriber>> InputManager::subscribers;
std::shared_ptr<InputSubscriber> InputManager::NothingBurger = std::make_shared<InputSubscriber>();
std::shared_ptr<InputSubscriber> InputManager::CurrentSubscriber = NothingBurger;
GamepadInterpreter InputManager::pad(0);

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
    S::ControllerRecent = false;
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
      Pause(event.type == sf::Event::KeyPressed); return;
    default:
      return;
    }
  case (sf::Event::MouseButtonPressed):
  case (sf::Event::MouseButtonReleased):
    if (event.mouseButton.button == sf::Mouse::Left) {
      Select(S::CursorDown = event.type == sf::Event::MouseButtonPressed);
    } return;
  case (sf::Event::MouseMoved):
    CurrentSubscriber->Point({event.mouseMove.x, event.mouseMove.y});
    CurrentSubscriber->Look((Vector2f(event.mouseMove.x, event.mouseMove.y) - Vector2f(S::ScreenSize.x, S::ScreenSize.y) / 2).norm()); return;
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

bool InputManager::Up(bool down) {
  if (down != action_pressed[UP]) {
    action_pressed[UP] = down;
    CurrentSubscriber->Up(down);
    return down;
  }
  return false;
}

bool InputManager::Down(bool down) {
  if (down != action_pressed[DOWN]) {
    action_pressed[DOWN] = down;
    CurrentSubscriber->Down(down);
    return down;
  }
  return false;
}

bool InputManager::Left(bool down) {
  if (down != action_pressed[LEFT]) {
    action_pressed[LEFT] = down;
    CurrentSubscriber->Left(down);
    return down;
  }
  return false;
}

bool InputManager::Right(bool down) {
  if (down != action_pressed[RIGHT]) {
    action_pressed[RIGHT] = down;
    CurrentSubscriber->Right(down);
    return down;
  }
  return false;
}

bool InputManager::Select(bool down) {
  if (down != action_pressed[SELECT]) {
    action_pressed[SELECT] = down;
    CurrentSubscriber->Select(down);
    return down;
  }
  return false;
}

bool InputManager::Pause(bool down) {
  if (down != action_pressed[PAUSE]) {
    action_pressed[PAUSE] = down;
    CurrentSubscriber->Pause(down);
    return down;
  }
  return false;
}

void InputManager::update(float dt) {
  CurrentSubscriber = getCurrentSubscriber();
  if (S::ControllerConnected && (S::ControllerRecent || pad.pressed(0) || pad.getLeft().magSqr() > 0.1f)) {
    S::ControllerRecent = true;
    CurrentSubscriber->Move(pad.getLeft());
    CurrentSubscriber->Look(pad.getRight());

    Up(pad.lastL.y < -0.5f);
    Down(pad.lastL.y > 0.5f);
    Left(pad.lastL.x < -0.5f);
    Right(pad.lastL.x > 0.5f);
    Pause(pad.pressed(7));
    Select(pad.pressed(0));
  }
  else {
    CurrentSubscriber->Move({
        (action_pressed[LEFT] ? -1.0f : 0.0f) + (action_pressed[RIGHT] ? 1.0f : 0.0f),
        (action_pressed[UP] ? -1.0f : 0.0f) + (action_pressed[DOWN] ? 1.0f : 0.0f),
    });
  }

  // 0: A, 1: B, 2: X, 3: Y, 4: LB, 5: RB, 6: Select, 7: Start
  // triggers are axis Z
  // right stick is UV, down is positive V, right is positive U
  // left stick is XY, down is positive Y, right is positive X
  // D-pad is PovXPovY, down is negative Y, right is positive X
}

void InputManager::Resize() {
  S::ScreenSize = (Vector2f)S::Window.getSize();
  CurrentSubscriber->Resize();
}

void InputManager::StartController() {
  if (sf::Joystick::isConnected(0)) {
    S::ControllerConnected = true;
    S::ControllerRecent = true;

    pad.LDrift.reset();
    pad.RDrift.reset();
    pad.LDrift = pad.getLeft();
    pad.RDrift = pad.getRight();
  }
}
