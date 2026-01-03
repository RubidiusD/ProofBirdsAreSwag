#include "InputManager.h"

std::vector<std::shared_ptr<InputSubscriber>> InputManager::subscribers;

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
