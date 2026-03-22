#include "Settings.h"

bool S::CursorMode = false;
bool S::CursorDown = false;

Vector2f S::Res = {960, 540};
//sf::RenderWindow S::Window(sf::VideoMode::getFullscreenModes()[0], "Birds are pretty swag yo", sf::Style::Fullscreen);
sf::RenderWindow S::Window({960, 540}, "Birds are pretty swag yo");
Vector2f S::ScreenSize;
sf::View S::UI_View;
const float S::stick_tolerance = 10.0f;
