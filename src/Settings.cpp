#include "Settings.h"

bool S::CursorDown = false;
bool S::ControllerConnected = false;
bool S::ControllerRecent = false;
unsigned S::player_index = 0;
Vector2f S::mouse;

bool S::bird2 = false;
bool S::bird3 = false;
bool S::bird4 = false;

Vector2f S::Res = {960, 540};
sf::RenderWindow S::Window(sf::VideoMode::getFullscreenModes()[0], "Birds are pretty swag yo", sf::Style::Fullscreen);
//sf::RenderWindow S::Window({960, 540}, "Birds are pretty swag yo");
Vector2f S::ScreenSize;
sf::View S::UI_View;
const float S::stick_tolerance = 4.0f;
