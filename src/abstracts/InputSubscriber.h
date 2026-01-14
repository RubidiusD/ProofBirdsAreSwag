#ifndef BIRDSARESWAG_INPUT_SUBSCRIBER_H
#define BIRDSARESWAG_INPUT_SUBSCRIBER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

enum InputActions {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SELECT,
  TOTAL
};

class InputSubscriber {
public:
  bool listening_to_inputs = false;
  unsigned subscriber_id = 0;
  virtual void Up(bool down) {}
  virtual void Down(bool down) {}
  virtual void Left(bool down) {}
  virtual void Right(bool down) {}
  virtual void Select(bool down) {}
  virtual void Move(const sf::Vector2f& vector) {} // relative to the player, made of the left joystick or wasd
  virtual void Look(const sf::Vector2f& vector) {} // relative to the player, made of mouse or right joystick
  virtual void Point(const sf::Vector2f& vector) {} // position on the screen
  virtual void KeyPressed(sf::Keyboard::Key key, bool down) {}
  virtual void ManageInputs(sf::Event event) {}
  virtual void Resize() {}
};

#endif // BIRDSARESWAG_INPUT_SUBSCRIBER_H
