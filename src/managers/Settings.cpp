#include "Settings.h"

bool S::dlc[3] = {true, false, false};
bool S::rubiTweaks = false;
bool S::CursorMode = false;
bool S::CursorDown = false;

sf::RenderWindow S::Window(sf::VideoMode::getFullscreenModes()[0], "Quacks of Quedlinburg", sf::Style::Fullscreen);
sf::Vector2f S::Res;