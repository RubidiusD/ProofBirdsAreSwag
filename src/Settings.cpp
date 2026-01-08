#include "Settings.h"

bool S::CursorMode = false;
bool S::CursorDown = false;

sf::RenderWindow S::Window(sf::VideoMode::getFullscreenModes()[0], "Birds are pretty swag yo", sf::Style::Fullscreen);
sf::Vector2f S::Res = {960, 540};
sf::Vector2f S::ScreenSize;
sf::View S::UI_View;
