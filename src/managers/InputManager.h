#ifndef BIRDSARESWAG_INPUTMANAGER_H
#define BIRDSARESWAG_INPUTMANAGER_H

#include "../abstracts/InputSubscriber.h"
#include "GamepadInterpreter.h"
#include <memory>
#include <vector>

class InputManager {
private:
  static bool action_pressed[TOTAL];
  static std::vector<std::shared_ptr<InputSubscriber>> subscribers;
  static std::shared_ptr<InputSubscriber> NothingBurger;
  static std::shared_ptr<InputSubscriber> CurrentSubscriber;

  static const std::shared_ptr<InputSubscriber>& getCurrentSubscriber();

  static GamepadInterpreter pad;

  static void Up(bool down);
  static void Down(bool down);
  static void Left(bool down);
  static void Right(bool down);
  static void Select(bool down);
  static void Pause(bool down);
public:
  static void subscribe(InputSubscriber* new_subscriber);
  static void remove(InputSubscriber* new_subscriber);
  static void manageInput(sf::Event event);
  static void update(float dt);
  static void Resize();
  static void StartController();
};

#endif // BIRDSARESWAG_INPUTMANAGER_H
