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
    src/managers/GamepadInterpreter.h
    src/Settings.h src/Settings.cpp

    src/abstracts/AbstractAction.h src/abstracts/AbstractAction.cpp
    src/abstracts/InputSubscriber.h


    src/Game.h src/Game.cpp

    src/menus/ScreenElements/AbstractButton.h
    src/menus/ScreenElements/TextButton.h
    src/menus/ScreenElements/DragButton.h

    src/menus/AbstractMenu.h src/menus/AbstractMenu.cpp
    src/menus/SplashScreen.h src/menus/SplashScreen.cpp
    src/menus/MainMenu.h src/menus/MainMenu.cpp
    src/menus/PauseMenu.h src/menus/PauseMenu.cpp
    src/menus/ResultsMenu.h src/menus/ResultsMenu.cpp

    src/LevelElements/CircleCollider.h
    src/LevelElements/AbstractLevelElement.h
    src/LevelElements/AbstractCircle.h src/LevelElements/AbstractCircle.cpp

    src/LevelElements/scenery/Surface.h src/LevelElements/scenery/Surface.cpp
    src/LevelElements/scenery/AbstractWind.h
    src/LevelElements/scenery/Billboard.h

    src/LevelElements/enemies/AbstractBird.h src/LevelElements/enemies/AbstractBird.cpp
    src/LevelElements/enemies/Bird1.h src/LevelElements/enemies/Bird1.cpp
    src/LevelElements/enemies/Bird2.h src/LevelElements/enemies/Bird2.cpp
    src/LevelElements/enemies/Bird3.h src/LevelElements/enemies/Bird3.cpp
    src/LevelElements/enemies/Bird4.h src/LevelElements/enemies/Bird4.cpp

    src/LevelElements/players/AbstractPlayer.h src/LevelElements/players/AbstractPlayer.cpp
    src/LevelElements/players/BirdPlayer.h src/LevelElements/players/BirdPlayer.cpp
    src/LevelElements/players/CursorPlayer.h src/LevelElements/players/CursorPlayer.cpp

    src/LevelElements/util/AbstractBox.h
    src/LevelElements/util/PlayerListener.h src/LevelElements/util/PlayerListener.cpp
    src/LevelElements/util/EndLevelTrigger.h
    src/LevelElements/util/SpawnTrigger.h
    src/LevelElements/util/AbstractLine.h src/LevelElements/util/AbstractLine.cpp
    src/LevelElements/util/ProgressTrigger.h src/LevelElements/util/ProgressTrigger.cpp
    src/LevelElements/util/SurfaceToggleTrigger.h
    src/LevelElements/util/ProgressData.h

    src/LevelElements/projectiles/Egg.h src/LevelElements/projectiles/Egg.cpp

    src/LevelElements/fx/Particle.h src/LevelElements/fx/Particle.cpp
    src/LevelElements/fx/EggParticle.h

    src/levels/LevelLoader.hpp
    src/levels/LevelLibrary.h src/levels/LevelLibrary.cpp
    src/levels/AbstractLevel.h src/levels/AbstractLevel.cpp
    src/levels/FlyingLevel.h src/levels/FlyingLevel.cpp
    src/levels/TestLevel.h src/levels/TestLevel.cpp
    src/levels/TrackingLevel.h src/levels/TrackingLevel.cpp
)
add_executable(BirdsAreSwag ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (BirdsAreSwag sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)