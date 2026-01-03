#ifndef BIRDSARESWAG_INPUTMANAGER_H
#define BIRDSARESWAG_INPUTMANAGER_H

#include "../abstracts/InputSubscriber.h"
#include <memory>
#include <vector>

class InputManager {
private:
  static std::vector<std::shared_ptr<InputSubscriber>> subscribers;
public:
  static void subscribe(InputSubscriber* new_subscriber);
  static void remove(InputSubscriber* new_subscriber);
};

#endif // BIRDSARESWAG_INPUTMANAGER_H
