#ifndef BIRDSARESWAG_INPUT_SUBSCRIBER_H
#define BIRDSARESWAG_INPUT_SUBSCRIBER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class InputSubscriber {
public:
  bool listening_to_inputs = false;
  unsigned subscriber_id;
  virtual void Up(bool down) {}
  virtual void Down(bool down) {}
  virtual void Left(bool down) {}
  virtual void Right(bool down) {}
  virtual void Move(sf::Vector2f vector) {}
  virtual void Select() {}
  virtual void ManageInputs(sf::Event event) {}
};

#endif // BIRDSARESWAG_INPUT_SUBSCRIBER_H
