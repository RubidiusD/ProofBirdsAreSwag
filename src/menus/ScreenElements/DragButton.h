#ifndef BIRDSARESWAG_DRAG_BUTTON_H
#define BIRDSARESWAG_DRAG_BUTTON_H

#include "TextButton.h"

class DragButton : public TextButton {
protected:
  sf::String pre_number_string;
  sf::String post_number_string;
  float min;
  float max;
  Vector2f pos_on_click;
  float value = 10.0f;
  float value_on_click = 10.0f;

  void UpdateText() {
    text.setString(pre_number_string + std::to_string((int)value) + post_number_string);
  }
public:
  DragButton(unsigned font, const sf::String& textL, float lower, float higher, const sf::String& textR, const Neighbours& n, const Vector2f& ratio_) : TextButton(font, textL + textR, n, ratio_) {
    min = lower;
    max = higher;
    pre_number_string = textL;
    post_number_string = textR;
    UpdateText();
  }

  void Press() override {
    pos_on_click = S::mouse;
    value_on_click = value;
  }

  void Drag(const Vector2f& vector) override {
    value = fmaxf(min, fminf(max,
      value_on_click + (vector.x - pos_on_click.x) * 20.0f / S::Res.x
    ));
    UpdateText();
  }
};

#endif // BIRDSARESWAG_DRAG_BUTTON_H
