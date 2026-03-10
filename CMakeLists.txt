cmake_minimum_required(VERSION 3.14)
project(BirdsAreSwag)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

#---- File management&  .exe creation ----#

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES
    src/main.cpp
    src/MathLib.h src/MathLib.cpp
    src/Vector2f.hpp

    src/managers/ActionManager.h src/managers/ActionManager.cpp
    src/managers/MenuManager.h src/managers/MenuManager.cpp
    src/managers/AssetManager.h src/managers/AssetManager.cpp
    src/managers/InputManager.h src/managers/InputManager.cpp
    src/Settings.h src/Settings.cpp

    src/abstracts/AbstractMenu.h src/abstracts/AbstractMenu.cpp
    src/abstracts/AbstractAction.h src/abstracts/AbstractAction.cpp
    src/abstracts/InputSubscriber.h

    src/abstracts/ScreenElements/AbstractButton.h src/abstracts/ScreenElements/AbstractButton.cpp
    src/abstracts/ScreenElements/TextButton.h src/abstracts/ScreenElements/TextButton.cpp

    src/birds/Game.h src/birds/Game.cpp
    src/birds/menus/SplashScreen.h src/birds/menus/SplashScreen.cpp
    src/birds/menus/MainMenu.h src/birds/menus/MainMenu.cpp
    src/birds/menus/PauseMenu.h src/birds/menus/PauseMenu.cpp
    src/birds/menus/ResultsMenu.h src/birds/menus/ResultsMenu.cpp

    src/birds/LevelElements/CircleCollider.h
    src/birds/LevelElements/AbstractLevelElement.h
    src/birds/LevelElements/AbstractCircle.h src/birds/LevelElements/AbstractCircle.cpp

    src/birds/LevelElements/scenery/Surface.h src/birds/LevelElements/scenery/Surface.cpp
    src/birds/LevelElements/scenery/AbstractWind.h
    src/birds/LevelElements/scenery/Billboard.h

    src/birds/LevelElements/enemies/Bird1.h src/birds/LevelElements/enemies/Bird1.cpp
    src/birds/LevelElements/enemies/Bird2.h src/birds/LevelElements/enemies/Bird2.cpp

    src/birds/LevelElements/players/AbstractPlayer.h src/birds/LevelElements/players/AbstractPlayer.cpp
    src/birds/LevelElements/players/BirdPlayer.h src/birds/LevelElements/players/BirdPlayer.cpp
    src/birds/LevelElements/players/CursorPlayer.h src/birds/LevelElements/players/CursorPlayer.cpp

    src/birds/LevelElements/util/AbstractBox.h
    src/birds/LevelElements/util/PlayerListener.h src/birds/LevelElements/util/PlayerListener.cpp
    src/birds/LevelElements/util/EndLevelTrigger.h
    src/birds/LevelElements/util/SpawnTrigger.h

    src/birds/LevelElements/projectiles/Egg.h src/birds/LevelElements/projectiles/Egg.cpp

    src/birds/LevelElements/fx/Particle.h src/birds/LevelElements/fx/Particle.cpp
    src/birds/LevelElements/fx/EggParticle.h

    src/birds/levels/LevelLoader.hpp
    src/birds/levels/LevelLibrary.h src/birds/levels/LevelLibrary.cpp
    src/birds/levels/AbstractLevel.h src/birds/levels/AbstractLevel.cpp

    src/birds/levels/FlyingLevel.h src/birds/levels/FlyingLevel.cpp
    src/birds/levels/TestLevel.h src/birds/levels/TestLevel.cpp
    src/birds/levels/TrackingLevel.h src/birds/levels/TrackingLevel.cpp
    src/birds/LevelElements/util/AbstractLine.h
    src/birds/LevelElements/util/ProgressTrigger.h
    src/birds/LevelElements/util/AbstractLine.cpp
)
add_executable(BirdsAreSwag ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (BirdsAreSwag sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)