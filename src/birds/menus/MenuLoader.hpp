#ifndef BIRDSARESWAG_MENU_LOADER_HPP
#define BIRDSARESWAG_MENU_LOADER_HPP

#include "../../managers/AssetManager.h"
#include "../../managers/MenuManager.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "SplashScreen.h"

namespace MenuLoader {
static void LoadMenus() {
  MenuManager::registerMenu(std::make_shared<MainMenu>());
  MenuManager::registerMenu(std::make_shared<SplashScreen>());
  MenuManager::registerMenu(std::make_shared<PauseMenu>());

  AssetManager::RegisterFont("Data/fonts/monospace/MonospaceOblique.ttf", 0);
//  AssetManager::RegisterFont("Data/fonts/open-sans/OpenSans-Bold.ttf", 0);
}
}

#endif // BIRDSARESWAG_MENU_LOADER_HPP
