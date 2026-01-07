cmake_minimum_required(VERSION 3.14)
project(BirdsAreSwag)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

#---- File management & .exe creation ----#

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES
    src/main.cpp
    src/MathLib.h src/MathLib.cpp
    src/birds/Game.h src/birds/Game.cpp

    src/managers/ActionManager.h src/managers/ActionManager.cpp
    src/managers/MenuManager.h src/managers/MenuManager.cpp
    src/managers/AssetManager.h src/managers/AssetManager.cpp
    src/Settings.h src/Settings.cpp
    src/managers/InputManager.h src/managers/InputManager.cpp

    src/abstracts/AbstractMenu.h src/abstracts/AbstractMenu.cpp
    src/abstracts/AbstractAction.h src/abstracts/AbstractAction.cpp
    src/abstracts/InputSubscriber.h

    src/abstracts/ScreenElements/AbstractButton.h src/abstracts/ScreenElements/AbstractButton.cpp
    src/abstracts/ScreenElements/TextButton.h src/abstracts/ScreenElements/TextButton.cpp

    src/birds/menus/SplashScreen.h src/birds/menus/SplashScreen.cpp
    src/birds/menus/MainMenu.h src/birds/menus/MainMenu.cpp

    src/birds/abstracts/AbstractPlayer.h src/birds/abstracts/AbstractPlayer.cpp
    src/birds/abstracts/AbstractLevel.h src/birds/abstracts/AbstractLevel.cpp
    src/birds/abstracts/LevelElements/Surface.h src/birds/abstracts/LevelElements/Surface.cpp
    src/birds/levels/LevelLoader.hpp
    src/birds/levels/TestLevel.h src/birds/levels/TestLevel.cpp
    src/birds/levels/LevelLibrary.h src/birds/levels/LevelLibrary.cpp
)
add_executable(BirdsAreSwag ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (BirdsAreSwag sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)