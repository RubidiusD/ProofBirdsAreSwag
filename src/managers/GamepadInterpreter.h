#ifndef BIRDSARESWAG_GAMEPAD_INTERPRETER_H
#define BIRDSARESWAG_GAMEPAD_INTERPRETER_H

#include "../Vector2f.hpp"
#include <SFML/Window/Joystick.hpp>

struct GamepadInterpreter {
  explicit GamepadInterpreter(unsigned index) { i = index; }

  unsigned i = 0;
  Vector2f LDrift;
  Vector2f RDrift;

  Vector2f lastL;
  Vector2f lastR;

  Vector2f getLeft() {
    return lastL = (Vector2f(sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) / 100, sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 100) - LDrift);
  }

  Vector2f getRight() {
    return lastR = (Vector2f(sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::U) / 100, sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V) / 100) - RDrift);
  }

  Vector2f getDpad() const {
    return {sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::PovX) / 100, sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) / -100};
  }

  bool pressed(unsigned index) const {
    return sf::Joystick::isButtonPressed(i, index);
  }
};

#endif // BIRDSARESWAG_GAMEPAD_INTERPRETER_H
